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

namespace obotcha {

DECLARE_SIMPLE_CLASS(SocketMonitorTask) {
public:
    _SocketMonitorTask(int event,Socket s);
    _SocketMonitorTask(int event,Socket s,ByteArray);

    int event;
    ByteArray data;
    Socket sock;
};

DECLARE_SIMPLE_CLASS(SocketMonitor) {
public:
    _SocketMonitor();
    _SocketMonitor(int);

    int bind(Socket,SocketListener);
    int bind(ServerSocket,SocketListener);
    int bind(int,SocketListener);
    
    int remove(Socket);

    void release();
    
private:
    
    EPollFileObserver mPoll;

    Mutex mMutex;
    HashMap<int,Socket> mSocks;

    //Multi Threads
    int mThreadNum;
    ArrayList<LinkedList<SocketMonitorTask>>  mThreadLocalTasks;
    LinkedList<SocketMonitorTask> mThreadPublicTasks;
    ThreadPoolExecutor mExecutor;
    Socket *mCurrentSockets;
    Condition mCondition;

    //bool isStop
    mutable volatile int32_t isStop;

    int mServerSockFd;
    
    

};

}

#endif