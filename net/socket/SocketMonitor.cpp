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

//-----------SocketMonitorTask-----------
_SocketMonitorTask::_SocketMonitorTask(int event, Socket s, ByteArray data) {
    this->event = event;
    this->sock = s;
    this->data = data;
}

//-----------SocketInformation-----------
_SocketInformation::_SocketInformation(Socket sock,SocketListener listener) {
    this->sock = sock;
    this->listener = listener;
}

//-----------SocketMonitor-----------
_SocketMonitor::_SocketMonitor() : _SocketMonitor(4) {
    //Nothing
}

_SocketMonitor::_SocketMonitor(int threadnum,int recvBuffSize) {
    mAsyncOutputPool = createAsyncOutputChannelPool();
    mRecvBuffSize = recvBuffSize;
    mMutex = createMutex();
    // mClientSocks = createConcurrentHashMap<int, Socket>();
    // mServerSocks = createConcurrentHashMap<int, ServerSocket>();
    mSockInfos = createConcurrentHashMap<int,SocketInformation>();
    mPoll = createEPollFileObserver();
    mPoll->start();
    mPendingTasks = createLinkedList<SocketMonitorTask>();
    mCondition = createCondition();
    //mListeners = createConcurrentHashMap<int, SocketListener>();
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
                        task = localTasks->takeFirst();
                        if(task == nullptr) {
                            InfiniteLoop {
                                task = mPendingTasks->takeFirst();
                                if(task != nullptr) {
                                    int taskFd = task->sock->getFileDescriptor()->getFd();
                                    auto tasks = mThreadTaskMap->get(taskFd);
                                    if(tasks != nullptr && tasks != localTasks) {
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
                                mThreadTaskMap->remove(currentFd);
                                mCondition->wait(monitor->mMutex);
                                continue;
                            }
                        }
                    }
                    //Socket will be closed directly in websocket server.
                    //We should check whether socket is still connected
                    //to prevent nullpoint exception
                    //auto desc = task->sock->getFileDescriptor();
                    //SocketListener listener = monitor->mListeners->get(currentFd);
                    auto sockInfo = mSockInfos->get(currentFd);
                    if (sockInfo != nullptr) {
                        sockInfo->listener->onSocketMessage(task->event, task->sock,
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
    return bind(s,l,s->getProtocol() == st(NetProtocol)::Udp);
}

int _SocketMonitor::bind(ServerSocket s, SocketListener l) {
    return bind(s, l, true);
}

int _SocketMonitor::onServerEvent(int fd,uint32_t events) {
    auto sockInfo = mSockInfos->get(fd);
    if ((events & (EPOLLRDHUP | EPOLLHUP)) != 0) {
        if(sockInfo != nullptr) {
            sockInfo->listener->onSocketMessage(st(NetEvent)::Disconnect,sockInfo->sock,nullptr);
            unbind(sockInfo->sock);
        }
        return st(EPollFileObserver)::Remove;
    }

    //try check whether it is a udp
    if (sockInfo != nullptr && sockInfo->sock->getProtocol() == st(NetProtocol)::Udp) {
        Socket newClient = nullptr;
        ByteArray buff = nullptr;
        do {
            buff = createByteArray(mRecvBuffSize);
            auto stream = Cast<SocketInputStream>(sockInfo->sock->getInputStream());
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
        //ServerSocket server = mServerSocks->get(fd);
        ServerSocket server = Cast<ServerSocket>(sockInfo->sock);
        auto client = server->accept();
        if (client != nullptr) {
            bind(client,sockInfo->listener,false);
            Synchronized(mMutex) {
                mPendingTasks->putLast(createSocketMonitorTask(st(NetEvent)::Connect,client));
                mCondition->notify();
            }
        } else {
            LOG(ERROR)<<"SocketMonitor accept socket is a null socket!!!!";
        }
    }
    return st(EPollFileObserver)::OK;
}

int _SocketMonitor::onClientEvent(int fd,uint32_t events) {
    SocketInformation info = mSockInfos->get(fd);
    Inspect(info == nullptr,st(EPollFileObserver)::Remove)
    auto client = info->sock;
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

int _SocketMonitor::bind(Socket s, SocketListener l, bool isServer) {
    int fd = s->getFileDescriptor()->getFd();    
    Synchronized(mMutex) {
        if (isSocketExist(s)) {
            LOG(ERROR)<<"bind socket already exists!!!";
            return 0;
        }
        s->setAsync(true,mAsyncOutputPool);
        s->getFileDescriptor()->monitor();
        mSockInfos->put(fd,createSocketInformation(s,l));
    }

    //int serversocket = isServer?fd:-1;
    mPoll->addObserver(
        fd, EPOLLIN | EPOLLRDHUP | EPOLLHUP,
        [this](int fd, uint32_t events,bool isServer,SocketMonitor monitor) {
            if (isServer) {
                return onServerEvent(fd,events);
            } else {
                return onClientEvent(fd,events);
            }
        },
        isServer, AutoClone(this));

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

    // mClientSocks->clear();
    // mServerSocks->clear();

    // mListeners->clear();
    mSockInfos->clear();
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
        // mClientSocks->remove(fd->getFd());
        // mServerSocks->remove(fd->getFd());
        // mListeners->remove(fd->getFd());
        mSockInfos->remove(fd->getFd());
    }
    return 0;
}

bool _SocketMonitor::isSocketExist(Socket s) {
    int fd = s->getFileDescriptor()->getFd();
    //return mClientSocks->get(fd) != nullptr;
    return mSockInfos->get(fd) != nullptr;
}

bool _SocketMonitor::isPendingTasksEmpty() {
    return mPendingTasks->size() == 0;
}

// bool _SocketMonitor::isClientSocketsEmpty() {
//     return mClientSocks->size() == 0;
// }

// bool _SocketMonitor::isServerSocksEmpty() {
//     return mServerSocks->size() == 0;
// }

_SocketMonitor::~_SocketMonitor() {
    close();
    mExecutor->awaitTermination();
}

} // namespace obotcha
