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
    _SocketMonitor(int);
    ~_SocketMonitor();

    int bind(Socket,SocketListener);
    int bind(ServerSocket,SocketListener);
   
    int remove(Socket,bool isClose = false);
    int remove(ServerSocket,bool isClose = false);

    void close();

    void dump();
    
private:
    void addNewSocket(Socket s,SocketListener l);
    bool isSocketExist(Socket s);
    int bind(int,SocketListener,bool isServer = false);
    int _remove(FileDescriptor);

    EPollFileObserver mPoll;
    ConcurrentHashMap<int,Socket> mSocks;
    ConcurrentHashMap<int,ServerSocket> mServerSocks;

    int mThreadNum;

    Mutex mMutex;
    int *currentProcessingFds;
    LinkedList<SocketMonitorTask> mThreadPublicTasks;

    //wangsl
    HashMap<int,ConcurrentLinkedList<SocketMonitorTask>> mThreadTaskMap;
    //wangsl
    
    ThreadPoolExecutor mExecutor;
    Condition mCondition;

    ConcurrentHashMap<int,SocketListener> mListeners;

    mutable volatile bool isStop;
};

}

#endif