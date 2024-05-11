#include "SocketMonitor.hpp"
#include "ExecutorBuilder.hpp"
#include "Log.hpp"
#include "Inspect.hpp"

#include "TimeWatcher.hpp"
#include "Synchronized.hpp"
#include "OStdInstanceOf.hpp"
#include "ServerSocket.hpp"
#include "Process.hpp"

namespace obotcha {

//-----------SocketMonitorTask-----------
_SocketMonitorTask::_SocketMonitorTask(st(Net)::Event _event, Socket _s, ByteArray _data):
                                        event(_event),data(_data),sock(_s) {
}

//-----------SocketInformation-----------
_SocketInformation::_SocketInformation(Socket s,SocketListener l):sock(s),listener(l) {
}

//-----------SocketMonitor-----------
_SocketMonitor::_SocketMonitor() : _SocketMonitor(4) {
    //Nothing
}

_SocketMonitor::_SocketMonitor(int threadnum,int recvBuffSize):mRecvBuffSize(recvBuffSize) {
    mPoll->start();
    this->mExecutor = ExecutorBuilder::New()
                    ->setDefaultThreadNum(threadnum)
                    ->newThreadPool();
    for (int i = 0; i < threadnum; i++) {
        mExecutor->submit(
            [](SocketMonitor monitor) {
                SocketMonitorTask task = nullptr;
                int currentFd = -1;
                LinkedList<SocketMonitorTask> localTasks = LinkedList<SocketMonitorTask>::New();

                while (!monitor->mIsSusspend) {
                    {
                        AutoLock l(monitor->mMutex);
                        task = localTasks->takeFirst();
                        if(task == nullptr) {
                            while(true) {
                                task = monitor->mPendingTasks->takeFirst();
                                if(task != nullptr) {
                                    int taskFd = task->sock->getFileDescriptor()->getFd();
                                    auto tasks = monitor->mThreadTaskMap->get(taskFd);
                                    if(tasks != nullptr && tasks != localTasks) {
                                        tasks->putLast(task);
                                        continue;
                                    } else {
                                        monitor->mThreadTaskMap->remove(currentFd);
                                        monitor->mThreadTaskMap->put(taskFd,localTasks);
                                        currentFd = taskFd;
                                    }
                                }
                                break;
                            }

                            if (task == nullptr) {
                                if(currentFd != -1) {
                                    monitor->mThreadTaskMap->remove(currentFd);
                                }
                                currentFd = -1;
                                monitor->mCondition->wait(monitor->mMutex);
                                continue;
                            }
                        }
                    }
                    //Socket will be closed directly in websocket server.
                    //We should check whether socket is still connected
                    //to prevent nullpoint exception
                    //auto desc = task->sock->getFileDescriptor();
                    auto sockInfo = monitor->mSockInfos->get(currentFd);
                    if (sockInfo != nullptr && sockInfo->listener != nullptr) {
                        sockInfo->listener->onSocketMessage(task->event, task->sock,
                                                    task->data);
                    }
                    
                    if(task->event == st(Net)::Event::Disconnect) {
                        monitor->unbind(task->sock);
                    }
                }
                localTasks->clear();
            },
            AutoClone(this));
    }
}

int _SocketMonitor::bind(Socket s, SocketListener l) {
    return bind(s,l,s->getProtocol() == st(Net)::Protocol::Udp
            ||IsInstance(ServerSocket, s));
}

st(IO)::Epoll::Result _SocketMonitor::onServerEvent(int fd,uint32_t events) {
    auto sockInfo = mSockInfos->get(fd);
    if ((events & (EPOLLRDHUP | EPOLLHUP)) != 0) {
        if(sockInfo != nullptr && sockInfo->listener != nullptr) {
            sockInfo->listener->onSocketMessage(st(Net)::Event::Disconnect,sockInfo->sock,nullptr);
            unbind(sockInfo->sock);
        }
        return st(IO)::Epoll::Result::Remove;
    }

    //try check whether it is a udp
    if (sockInfo != nullptr && 
        sockInfo->sock->getProtocol() == st(Net)::Protocol::Udp) {
        Socket newClient = nullptr;
        ByteArray buff = nullptr;
        do {
            buff = ByteArray::New(mRecvBuffSize);
            auto stream = Cast<SocketInputStream>(sockInfo->sock->getInputStream());
            auto newClient = stream->recvDatagram(buff);
            if(newClient == nullptr) {
                break;
            }
            Synchronized(mMutex) {
                mPendingTasks->putLast(SocketMonitorTask::New(st(Net)::Event::Message,
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
    return st(IO)::Epoll::Result::Ok;
}

int _SocketMonitor::processNewClient(Socket client,SocketListener listener) {
    int fd = client->getFileDescriptor()->getFd();    
    Synchronized(mMutex) {
        mSockInfos->put(fd,SocketInformation::New(client,listener));
        mPendingTasks->putLast(SocketMonitorTask::New(st(Net)::Event::Connect,client));
        mCondition->notify();
    }
    client->setAsync(true,mAsyncOutputPool);
    client->getFileDescriptor()->monitor();

    mPoll->addObserver(
        fd, EPOLLIN | EPOLLRDHUP | EPOLLHUP,
        [this](int fd_v, uint32_t events) {
            return onClientEvent(fd_v,events);
        });

    return 0;
}

st(IO)::Epoll::Result _SocketMonitor::onClientEvent(int fd,uint32_t events) {
    SocketInformation info = mSockInfos->get(fd);
    Inspect(info == nullptr,st(IO)::Epoll::Result::Remove)
    auto client = info->sock;
    if ((events & EPOLLIN) != 0) {
        auto inputStream = client->getInputStream();
        if(inputStream != nullptr) {
            long length = 0;
            do {
                ByteArray buff = ByteArray::New(mRecvBuffSize);
                length = inputStream->read(buff);
                if (length > 0) {
                    buff->quickShrink(length);
                    AutoLock l(mMutex);
                    mPendingTasks->putLast(SocketMonitorTask::New(st(Net)::Event::Message,
                                                                    client,
                                                                    buff));
                    mCondition->notify();
                }
            } while (length == mRecvBuffSize);
        }
    }
    if ((events & (EPOLLRDHUP | EPOLLHUP)) != 0) {
        AutoLock l(mMutex);
        mPendingTasks->putLast(SocketMonitorTask::New(st(Net)::Event::Disconnect, client));
        mCondition->notify();
        //return st(IO)::Epoll::Result::Remove;
    }
    return st(IO)::Epoll::Result::Ok;
}

int _SocketMonitor::bind(Socket s, SocketListener l, bool isServer) {
    int fd = s->getFileDescriptor()->getFd();    
    Synchronized(mMutex) {
        if (isSocketExist(s)) {
            LOG(ERROR)<<"bind socket already exists!!!,fd is "<<fd;
            return 0;
        }
        mSockInfos->put(fd,SocketInformation::New(s,l));
    }
    s->setAsync(true,mAsyncOutputPool);
    s->getFileDescriptor()->monitor();

    mPoll->addObserver(
        fd, EPOLLIN | EPOLLRDHUP | EPOLLHUP,
        [this](int fd_v, uint32_t events,bool isServer_v) {
            if (isServer_v) {
                return onServerEvent(fd_v,events);
            } else {
                return onClientEvent(fd_v,events);
            }
        },isServer);
    return 0;
}

void _SocketMonitor::close() {
    mPoll->close();
    Synchronized(mMutex) {
        Inspect(mIsSusspend)
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

bool _SocketMonitor::isSocketExist(Socket s) const {
    int fd = s->getFileDescriptor()->getFd();
    return mSockInfos->get(fd) != nullptr;
}

bool _SocketMonitor::isPendingTasksEmpty() const {
    return mPendingTasks->size() == 0;
}

int _SocketMonitor::getPendingTaskSize()  const {
    return mPendingTasks->size();
}

bool _SocketMonitor::isMonitorSocketEmpty() const {
    return mSockInfos->size() == 0;
}

_SocketMonitor::~_SocketMonitor() {
    close();
    mExecutor->awaitTermination();
}

} // namespace obotcha
