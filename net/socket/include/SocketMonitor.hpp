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

    EPollObserver mPoll = createEPollObserver();
    ConcurrentHashMap<int,SocketInformation> mSockInfos = createConcurrentHashMap<int,SocketInformation>();

    int mRecvBuffSize;
    Mutex mMutex = createMutex();
    LinkedList<SocketMonitorTask> mPendingTasks = createLinkedList<SocketMonitorTask>();
    HashMap<int,LinkedList<SocketMonitorTask>> mThreadTaskMap
                                    = createHashMap<int,LinkedList<SocketMonitorTask>>();
    ThreadPoolExecutor mExecutor;
    Condition mCondition = createCondition();
    AsyncOutputChannelPool mAsyncOutputPool = createAsyncOutputChannelPool();

    std::atomic<bool> mIsSusspend = false;
};

}

#endif
