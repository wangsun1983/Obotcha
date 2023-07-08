#include "SocketMonitor.hpp"
#include "ExecutorBuilder.hpp"
#include "Log.hpp"
#include "Inspect.hpp"
#include "NetEvent.hpp"
#include "TimeWatcher.hpp"
#include "Definations.hpp"
#include "Synchronized.hpp"
#include "InfiniteLoop.hpp"
#include "OStdInstanceOf.hpp"
#include "ServerSocket.hpp"
#include "Process.hpp"

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
    mSockInfos = createConcurrentHashMap<int,SocketInformation>();
    mPoll = createEPollFileObserver();
    mPoll->start();
    mPendingTasks = createLinkedList<SocketMonitorTask>();
    mCondition = createCondition();
    mIsSusspend = false;
    mThreadTaskMap = createHashMap<int,LinkedList<SocketMonitorTask>>();

    this->mExecutor = createExecutorBuilder()
                    ->setDefaultThreadNum(threadnum)
                    ->newThreadPool();

    for (int i = 0; i < threadnum; i++) {
        mExecutor->submit(
            [&](int index, SocketMonitor monitor) {
                SocketMonitorTask task = nullptr;
                int currentFd = -1;
                LinkedList<SocketMonitorTask> localTasks = createLinkedList<SocketMonitorTask>();

                while (!monitor->mIsSusspend) {
                    {
                        AutoLock l(mMutex);
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
                                        mThreadTaskMap->remove(currentFd);
                                        mThreadTaskMap->put(taskFd,localTasks);
                                        currentFd = taskFd;
                                    }
                                }
                                break;
                            }

                            if (task == nullptr) {
                                mThreadTaskMap->remove(currentFd);
                                currentFd = -1;
                                mCondition->wait(monitor->mMutex);
                                continue;
                            }
                        }
                    }
                    //Socket will be closed directly in websocket server.
                    //We should check whether socket is still connected
                    //to prevent nullpoint exception
                    //auto desc = task->sock->getFileDescriptor();
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
    return bind(s,l,s->getProtocol() == st(NetProtocol)::Udp||IsInstance(ServerSocket, s));
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
        ServerSocket server = Cast<ServerSocket>(sockInfo->sock);
        auto client = server->accept();
        if (client != nullptr) {
            processNewClient(client,sockInfo->listener);
        } else {
            LOG(ERROR)<<"SocketMonitor accept socket is a null socket!!!!";
        }
    }
    return st(EPollFileObserver)::OK;
}

int _SocketMonitor::processNewClient(Socket client,SocketListener listener) {
    int fd = client->getFileDescriptor()->getFd();    
    Synchronized(mMutex) {
        mSockInfos->put(fd,createSocketInformation(client,listener));
        mPendingTasks->putLast(createSocketMonitorTask(st(NetEvent)::Connect,client));
        mCondition->notify();
    }
    client->setAsync(true,mAsyncOutputPool);
    client->getFileDescriptor()->monitor();

    mPoll->addObserver(
        fd, EPOLLIN | EPOLLRDHUP | EPOLLHUP,
        [this](int fd, uint32_t events) {
            return onClientEvent(fd,events);
        });
    return 0;
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
        mSockInfos->put(fd,createSocketInformation(s,l));
    }
    s->setAsync(true,mAsyncOutputPool);
    s->getFileDescriptor()->monitor();

    mPoll->addObserver(
        fd, EPOLLIN | EPOLLRDHUP | EPOLLHUP,
        [this](int fd, uint32_t events,bool isServer) {
            if (isServer) {
                return onServerEvent(fd,events);
            } else {
                return onClientEvent(fd,events);
            }
        },isServer);
    return 0;
}

void _SocketMonitor::close() {
    mPoll->close();
    Synchronized(mMutex) {
        Inspect(mIsSusspend);
        mIsSusspend = true;
        mPendingTasks->clear();
        mCondition->notifyAll();
    }

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

int _SocketMonitor::remove(FileDescriptor fd) {
    if(fd != nullptr) {
        mPoll->removeObserver(fd->getFd());
        mSockInfos->remove(fd->getFd());
    }
    return 0;
}

bool _SocketMonitor::isSocketExist(Socket s) {
    int fd = s->getFileDescriptor()->getFd();
    return mSockInfos->get(fd) != nullptr;
}

bool _SocketMonitor::isPendingTasksEmpty() {
    return mPendingTasks->size() == 0;
}

_SocketMonitor::~_SocketMonitor() {
    close();
    mExecutor->awaitTermination();
}

} // namespace obotcha
