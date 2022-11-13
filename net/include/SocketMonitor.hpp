#ifndef __OBOTCHA_SOCKET_MONITOR_HPP__
#define __OBOTCHA_SOCKET_MONITOR_HPP__

#include <map>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "Socket.hpp"
#include "EPollFileObserver.hpp"
#include "SocketListener.hpp"
#include "ServerSocket.hpp"
#include "HashMap.hpp"
#include "Mutex.hpp"
#include "LinkedList.hpp"
#include "ArrayList.hpp"
#include "ThreadPoolExecutor.hpp"
#include "SpinLock.hpp"
#include "Closeable.hpp"
#include "ConcurrentHashMap.hpp"
#include "ConcurrentLinkedList.hpp"

namespace obotcha {

DECLARE_CLASS(SocketMonitorTask) {
public:
    _SocketMonitorTask(int event,Socket s,ByteArray data = nullptr);

    int event;
    ByteArray data;
    Socket sock;
};

DECLARE_CLASS(SocketMonitor) IMPLEMENTS(Closeable){
public:
    _SocketMonitor();
    _SocketMonitor(int,int recvBuffSize = st(SocketOption)::DefaultBuffSize);
    ~_SocketMonitor();

    int bind(Socket,SocketListener);
    int bind(ServerSocket,SocketListener);
   
    int unbind(Socket,bool isAutoClose = true);
    int unbind(ServerSocket,bool isAutoClose = true);

    void close();

    void dump();
    
private:
    bool isSocketExist(Socket s);
    int bind(int,SocketListener,bool isServer = false);
    int remove(FileDescriptor);

    int onServerEvent(int fd,uint32_t events,SocketListener &listener);
    int onClientEvent(int fd,uint32_t events,SocketListener &listener);

    EPollFileObserver mPoll;
    ConcurrentHashMap<int,Socket> mClientSocks;
    ConcurrentHashMap<int,ServerSocket> mServerSocks;

    int mThreadNum;

    int mRecvBuffSize;

    Mutex mMutex;
    //int *currentProcessingFds;
    LinkedList<SocketMonitorTask> mPendingTasks;

    //wangsl
    HashMap<int,LinkedList<SocketMonitorTask>> mThreadTaskMap;
    //wangsl
    
    ThreadPoolExecutor mExecutor;
    Condition mCondition;

    ConcurrentHashMap<int,SocketListener> mListeners;

    AsyncOutputChannelPool mAsyncOutputPool;

    mutable volatile bool isStop;
};

}

#endif