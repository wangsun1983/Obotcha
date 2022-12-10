#include "SocketMonitor.hpp"
#include "ExecutorBuilder.hpp"
#include "Log.hpp"
#include "Inspect.hpp"
#include "NetEvent.hpp"
#include "TimeWatcher.hpp"
#include "Definations.hpp"
#include "Synchronized.hpp"
#include "InfiniteLoop.hpp"

namespace obotcha {

_SocketMonitorTask::_SocketMonitorTask(int event, Socket s, ByteArray data) {
    this->event = event;
    this->sock = s;
    this->data = data;
}

_SocketMonitor::_SocketMonitor() : _SocketMonitor(4) {}

_SocketMonitor::_SocketMonitor(int threadnum,int recvBuffSize) {
    mAsyncOutputPool = createAsyncOutputChannelPool();

    mRecvBuffSize = recvBuffSize;

    mMutex = createMutex();
    mClientSocks = createConcurrentHashMap<int, Socket>();
    mServerSocks = createConcurrentHashMap<int, ServerSocket>();
    //currentProcessingFds = new int[threadnum];

    mPoll = createEPollFileObserver();
    mPoll->start();
    mPendingTasks = createLinkedList<SocketMonitorTask>();
    mCondition = createCondition();

    mListeners = createConcurrentHashMap<int, SocketListener>();
    mThreadNum = threadnum;
    isStop = false;

    mThreadTaskMap = createHashMap<int,LinkedList<SocketMonitorTask>>();

    this->mExecutor = createExecutorBuilder()
                    ->setDefaultThreadNum(mThreadNum)
                    ->newThreadPool();

    for (int i = 0; i < mThreadNum; i++) {
        mExecutor->submit(
            [this](int index, SocketMonitor monitor) {
                SocketMonitorTask task = nullptr;
                int currentFd = -1;
                LinkedList<SocketMonitorTask> localTasks = createLinkedList<SocketMonitorTask>();
                
                while (!monitor->isStop) {
                    //check myself task
                    {
                        AutoLock l(monitor->mMutex);
                        if(currentFd != -1) {
                            task = localTasks->takeFirst();
                        }
                        if(task == nullptr) {
                            if(currentFd != -1) {
                                mThreadTaskMap->remove(currentFd);
                                currentFd = -1;
                            }
                            InfiniteLoop {
                                task = mPendingTasks->takeFirst();
                                if(task != nullptr) {
                                    int taskFd = task->sock->getFileDescriptor()->getFd();
                                    auto tasks = mThreadTaskMap->get(taskFd);
                                    if(tasks != nullptr) {
                                        tasks->putLast(task);
                                        continue;
                                    } else {
                                        mThreadTaskMap->put(taskFd,localTasks);
                                        currentFd = taskFd;
                                    }
                                }
                                break;
                            }

                            if (task == nullptr) {
                                mCondition->wait(monitor->mMutex);
                                continue;
                            }
                        }
                    }
                    //Socket will be closed directly in websocket server.
                    //We should check whether socket is still connected
                    //to prevent nullpoint exception
                    //autoauto desc = task->sock->getFileDescriptor();
                    SocketListener listener = monitor->mListeners->get(currentFd);
                    if (listener != nullptr) {
                        listener->onSocketMessage(task->event, task->sock,
                                                    task->data);
                    }
                    
                    if(task->event == st(NetEvent)::Disconnect) {
                        unbind(task->sock);
                    }
                }
                localTasks->clear();
            },
            i, AutoClone(this));
    }
}

int _SocketMonitor::bind(Socket s, SocketListener l) {
    AutoLock ll(mMutex);
    if (isSocketExist(s)) {
        LOG(ERROR)<<"bind socket already exists!!!";
        return 0;
    }
    auto descriptor = s->getFileDescriptor();
    int fd = descriptor->getFd();
    mClientSocks->put(fd, s);
    mListeners->put(fd, l);
    
    s->setAsync(true,mAsyncOutputPool);
    s->getFileDescriptor()->monitor();
    return bind(fd, 
                l, 
                s->getProtocol() == st(NetProtocol)::Udp);
}

int _SocketMonitor::bind(ServerSocket s, SocketListener l) {
    mServerSocks->put(s->getFileDescriptor()->getFd(), s);
    s->getFileDescriptor()->monitor();

    return bind(s->getFileDescriptor()->getFd(), l, true);
}

int _SocketMonitor::onServerEvent(int fd,uint32_t events,SocketListener &listener) {
    if ((events & (EPOLLRDHUP | EPOLLHUP)) != 0) {
        auto server = mServerSocks->get(fd);
        if(server != nullptr) {
            listener->onSocketMessage(st(NetEvent)::Disconnect,server,nullptr);
            unbind(server);
        }
        return st(EPollFileObserver)::Remove;
    }
    
    //try check whether it is a udp
    Socket soc = mClientSocks->get(fd);
    if (soc != nullptr && soc->getProtocol() == st(NetProtocol)::Udp) {
        Socket newClient = nullptr;
        ByteArray buff = nullptr;
        do {
            buff = createByteArray(mRecvBuffSize);
            auto stream = Cast<SocketInputStream>(soc->getInputStream());
            if((newClient = stream->recvDatagram(buff)) == nullptr) {
                break;
            }
            
            Synchronized(mMutex) {
                mPendingTasks->putLast(createSocketMonitorTask(st(NetEvent)::Message, 
                                                                newClient,
                                                                buff));
                mCondition->notify();
            }
        } while(buff->size() == mRecvBuffSize);
    } else {
        ServerSocket server = mServerSocks->get(fd);
        soc = server->accept();
        if (soc != nullptr) {
            bind(soc,listener);
            Synchronized(mMutex) {
                mPendingTasks->putLast(createSocketMonitorTask(st(NetEvent)::Connect,soc));
                mCondition->notify();
            }
        } else {
            LOG(ERROR)<<"SocketMonitor accept socket is a null socket!!!!";
        }
    }
    return st(EPollFileObserver)::OK;
}

int _SocketMonitor::onClientEvent(int fd,uint32_t events,SocketListener &listener) {
    Socket client = mClientSocks->get(fd);
    Inspect(client == nullptr,st(EPollFileObserver)::Remove)

    if ((events & EPOLLIN) != 0) {
        auto inputStream = client->getInputStream();
        if(inputStream != nullptr) {
            long length = 0;
            do {
                ByteArray buff = createByteArray(mRecvBuffSize);
                length = inputStream->read(buff);
                if (length > 0) {
                    buff->quickShrink(length);
                    AutoLock l(mMutex);
                    mPendingTasks->putLast(createSocketMonitorTask(st(NetEvent)::Message, 
                                                                    client, 
                                                                    buff));
                    mCondition->notify();
                }
            } while (length == mRecvBuffSize);
        }
    }

    if ((events & (EPOLLRDHUP | EPOLLHUP)) != 0) {
        AutoLock l(mMutex);
        mPendingTasks->putLast(createSocketMonitorTask(st(NetEvent)::Disconnect, client));
        mCondition->notify();
        return st(EPollFileObserver)::Remove;
    }
    return st(EPollFileObserver)::OK;
}

int _SocketMonitor::bind(int fd, SocketListener l, bool isServer) {
    int serversocket = isServer?fd:-1;
    mPoll->addObserver(
        fd, EPOLLIN | EPOLLRDHUP | EPOLLHUP,
        [this](int fd, uint32_t events, SocketListener &listener, int serverfd,SocketMonitor monitor) {
            if (fd == serverfd) {
                return onServerEvent(fd,events,listener);
            } else {
                return onClientEvent(fd,events,listener);
            }
        },
        l, serversocket, AutoClone(this));

    return 0;
}

void _SocketMonitor::close() {
    mPoll->close();
    Synchronized(mMutex) {
        Inspect(isStop);
        isStop = true;

        mPendingTasks->clear();
        mCondition->notifyAll();
    }

    mClientSocks->clear();
    mServerSocks->clear();

    mListeners->clear();
    mExecutor->shutdown();
    //do not awaitTermination
    //mExecutor->awaitTermination();

    if(mAsyncOutputPool != nullptr) {
        mAsyncOutputPool->close();
    }
}

int _SocketMonitor::waitForExit(long interval) {
    return mExecutor->awaitTermination(interval);
}

void _SocketMonitor::dump() {
    printf("---SocketMonitor dump start --- \n");
    printf("mSocks size is %d \n",mClientSocks->size());
    mPoll->dump();
    printf("---SocketMonitor dump end --- \n");
}

int _SocketMonitor::unbind(Socket s,bool isAutoClose) {
    AutoLock l(mMutex);
    remove(s->getFileDescriptor());
    s->getFileDescriptor()->unMonitor(isAutoClose);
    return 0;
}

int _SocketMonitor::unbind(ServerSocket s,bool isAutoClose) {
    AutoLock l(mMutex);
    remove(s->getFileDescriptor());
    s->getFileDescriptor()->unMonitor(isAutoClose);
    return 0;
}

int _SocketMonitor::remove(FileDescriptor fd) {
    if(fd != nullptr) {
        mPoll->removeObserver(fd->getFd());
        mClientSocks->remove(fd->getFd());
        mServerSocks->remove(fd->getFd());
        mListeners->remove(fd->getFd());
    }
    return 0;
}

bool _SocketMonitor::isSocketExist(Socket s) {
    int fd = s->getFileDescriptor()->getFd();
    return mClientSocks->get(fd) != nullptr;
}

_SocketMonitor::~_SocketMonitor() {
    close();
    mExecutor->awaitTermination();
}

} // namespace obotcha
