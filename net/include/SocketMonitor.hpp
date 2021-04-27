#ifndef __OBOTCHA_SOCKET_MONITOR_HPP__
#define __OBOTCHA_SOCKET_MONITOR_HPP__

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

namespace obotcha {

DECLARE_SIMPLE_CLASS(SocketMonitorTask) {
public:
    _SocketMonitorTask(int event,Socket s,ByteArray data = nullptr);

    int event;
    ByteArray data;
    Socket sock;
};

DECLARE_SIMPLE_CLASS(SocketMonitor) {
public:
    _SocketMonitor();
    _SocketMonitor(int);
    ~_SocketMonitor();

    int bind(Socket,SocketListener);
    int bind(ServerSocket,SocketListener);
    
    int remove(Socket);

    void close();
    
private:
    void addNewSocket(Socket s,SocketListener l);
    bool isSocketExist(Socket s);
    int bind(int,SocketListener,bool isServer = false);

    EPollFileObserver mPoll;

    Mutex mMutex;
    HashMap<int,Socket> mSocks;

    HashMap<int,ServerSocket> mServerSocks;

    //Multi Threads
    int mThreadNum;
    ArrayList<LinkedList<SocketMonitorTask>>  mThreadLocalTasks;
    LinkedList<SocketMonitorTask> mThreadPublicTasks;
    ThreadPoolExecutor mExecutor;
    Socket *mCurrentSockets;
    Condition mCondition;

    SpinLock mListenerMutex;
    HashMap<int,SocketListener> mListeners;

    //bool isStop
    mutable volatile int32_t isStop;
};

}

#endif