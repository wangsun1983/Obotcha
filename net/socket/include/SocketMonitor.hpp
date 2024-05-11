#ifndef __OBOTCHA_SOCKET_MONITOR_HPP__
#define __OBOTCHA_SOCKET_MONITOR_HPP__

#include <atomic>

#include "Object.hpp"
#include "Socket.hpp"
#include "EPollObserver.hpp"
#include "SocketListener.hpp"
#include "HashMap.hpp"
#include "Mutex.hpp"
#include "LinkedList.hpp"
#include "ThreadPoolExecutor.hpp"
#include "Closeable.hpp"
#include "ConcurrentHashMap.hpp"


namespace obotcha {

DECLARE_CLASS(SocketMonitorTask) {
public:
    _SocketMonitorTask(st(Net)::Event event,Socket s,ByteArray data = nullptr);
    st(Net)::Event event;
    ByteArray data;
    Socket sock;
};

DECLARE_CLASS(SocketInformation) {
public:
    _SocketInformation(Socket,SocketListener);
    Socket sock;
    SocketListener listener;
};

DECLARE_CLASS(SocketMonitor) IMPLEMENTS(Closeable){
public:
    _SocketMonitor();
    _SocketMonitor(int threadnum,int recvBuffSize = st(SocketOption)::DefaultBuffSize);
    ~_SocketMonitor() override;

    int bind(Socket,SocketListener);

    int unbind(Socket,bool isAutoClose = true);

    void close() override;
    int waitForExit(long interval = 0);

    //used for test
    bool isPendingTasksEmpty() const;
    bool isMonitorSocketEmpty() const;
    int getPendingTaskSize() const;

private:
    bool isSocketExist(Socket s) const;
    int bind(Socket,SocketListener,bool isServer);
    int remove(FileDescriptor);

    st(IO)::Epoll::Result onServerEvent(int fd,uint32_t events);
    st(IO)::Epoll::Result onClientEvent(int fd,uint32_t events);
    int processNewClient(Socket client,SocketListener listener);

    EPollObserver mPoll = EPollObserver::New();
    ConcurrentHashMap<int,SocketInformation> mSockInfos = ConcurrentHashMap<int,SocketInformation>::New();

    int mRecvBuffSize;
    Mutex mMutex = Mutex::New();
    LinkedList<SocketMonitorTask> mPendingTasks = LinkedList<SocketMonitorTask>::New();
    HashMap<int,LinkedList<SocketMonitorTask>> mThreadTaskMap
                                    = HashMap<int,LinkedList<SocketMonitorTask>>::New();
    ThreadPoolExecutor mExecutor;
    Condition mCondition = Condition::New();
    AsyncOutputChannelPool mAsyncOutputPool = AsyncOutputChannelPool::New();

    std::atomic<bool> mIsSusspend = false;
};

}

#endif
