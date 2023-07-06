#ifndef __OBOTCHA_SOCKET_MONITOR_HPP__
#define __OBOTCHA_SOCKET_MONITOR_HPP__

#include "Object.hpp"

#include "Socket.hpp"
#include "EPollFileObserver.hpp"
#include "SocketListener.hpp"
#include "ServerSocket.hpp"
#include "HashMap.hpp"
#include "Mutex.hpp"
#include "LinkedList.hpp"
#include "ArrayList.hpp"
#include "ThreadPoolExecutor.hpp"
#include "Closeable.hpp"
#include "ConcurrentHashMap.hpp"

namespace obotcha {

DECLARE_CLASS(SocketMonitorTask) {
public:
    _SocketMonitorTask(int event,Socket s,ByteArray data = nullptr);

    int event;
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
    ~_SocketMonitor();

    int bind(Socket,SocketListener);
    int bind(ServerSocket,SocketListener);

    int unbind(Socket,bool isAutoClose = true);
    int unbind(ServerSocket,bool isAutoClose = true);

    void close();
    int waitForExit(long interval = 0);

    //used for test
    bool isPendingTasksEmpty();
    // bool isClientSocketsEmpty();
    // bool isServerSocksEmpty();

private:
    bool isSocketExist(Socket s);
    int bind(Socket,SocketListener,bool isServer);
    int remove(FileDescriptor);

    int onServerEvent(int fd,uint32_t events);
    int onClientEvent(int fd,uint32_t events);

    EPollFileObserver mPoll;
    //ConcurrentHashMap<int,Socket> mClientSocks;
    //ConcurrentHashMap<int,ServerSocket> mServerSocks;
    //ConcurrentHashMap<int,SocketListener> mListeners;
    ConcurrentHashMap<int,SocketInformation> mSockInfos;

    int mThreadNum;
    int mRecvBuffSize;
    Mutex mMutex;
    LinkedList<SocketMonitorTask> mPendingTasks;
    HashMap<int,LinkedList<SocketMonitorTask>> mThreadTaskMap;

    ThreadPoolExecutor mExecutor;
    Condition mCondition;
    
    AsyncOutputChannelPool mAsyncOutputPool;

    mutable volatile bool isStop;
};

}

#endif
