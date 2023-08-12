#ifndef __OBOTCHA_SOCKET_MONITOR_HPP__
#define __OBOTCHA_SOCKET_MONITOR_HPP__

#include "Object.hpp"

#include "Socket.hpp"
#include "EPollFileObserver.hpp"
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

    int onServerEvent(int fd,uint32_t events);
    int onClientEvent(int fd,uint32_t events);
    int processNewClient(Socket client,SocketListener listener);

    EPollFileObserver mPoll = createEPollFileObserver();
    ConcurrentHashMap<int,SocketInformation> mSockInfos = createConcurrentHashMap<int,SocketInformation>();

    int mRecvBuffSize;
    Mutex mMutex = createMutex();
    LinkedList<SocketMonitorTask> mPendingTasks = createLinkedList<SocketMonitorTask>();
    HashMap<int,LinkedList<SocketMonitorTask>> mThreadTaskMap
                                    = createHashMap<int,LinkedList<SocketMonitorTask>>();
    ThreadPoolExecutor mExecutor;
    Condition mCondition = createCondition();
    AsyncOutputChannelPool mAsyncOutputPool = createAsyncOutputChannelPool();

    mutable volatile bool mIsSusspend = false;
};

}

#endif
