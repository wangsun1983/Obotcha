#ifndef __OBOTCHA_HTTP_V1_SERVER_HPP__
#define __OBOTCHA_HTTP_V1_SERVER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HashMap.hpp"
#include "HttpCookie.hpp"
#include "TcpClient.hpp"
#include "HttpUrl.hpp"
#include "TcpServer.hpp"
#include "Mutex.hpp"
#include "SocketListener.hpp"
#include "HttpMultiPart.hpp"
#include "SSLServer.hpp"
#include "BlockingLinkedList.hpp"
#include "HashSet.hpp"
#include "ThreadPoolExecutor.hpp"
#include "HttpPacket.hpp"

namespace obotcha {

class _HttpV1ClientInfo;
class _HttpV1ResponseWriter;
class _HttpDispatcherPool;

DECLARE_SIMPLE_CLASS(DispatchHttpWorkData) {
public:
    _DispatchHttpWorkData(int,ByteArray,int);

    int fd;
    ByteArray pack;
    uint64_t clientid;
};

DECLARE_SIMPLE_CLASS(HttpV1Listener) {
public:
    virtual void onMessage(sp<_HttpV1ClientInfo> client,sp<_HttpV1ResponseWriter> w,HttpPacket msg) = 0;
    virtual void onConnect(sp<_HttpV1ClientInfo>) = 0;
    virtual void onDisconnect(sp<_HttpV1ClientInfo>) = 0;
    virtual ~_HttpV1Listener(){}
};


DECLARE_SIMPLE_CLASS(HttpDispatchRunnable) IMPLEMENTS(Runnable) {
public:
    _HttpDispatchRunnable(int index,sp<_HttpDispatcherPool>);
    void run();
    //void addDefferedTask(DispatchHttpWorkData);
    void release();

private:
    //Mutex mDefferedTaskMutex;
    Mutex mPoolMutex;
    //LinkedList<DispatchHttpWorkData> mDefferedTasks;
    sp<_HttpDispatcherPool> mPool;
    int mIndex;
};

DECLARE_SIMPLE_CLASS(HttpDefferedTasks) {
public:
    _HttpDefferedTasks();

    bool isDoDefferedTask;
    Mutex mutex;
    LinkedList<DispatchHttpWorkData> tasks;
};

DECLARE_SIMPLE_CLASS(HttpDispatcherPool) {
public:
    _HttpDispatcherPool(int threadNum = 4);
    void release();
    DispatchHttpWorkData getData(int);
    void addData(DispatchHttpWorkData);
    void clearFds(int index);

private:
    Mutex mDataMutex;
    Condition mDataCondition;

    ArrayList<HttpDefferedTasks> mDefferedTasks;
    LinkedList<DispatchHttpWorkData> datas;

    Mutex fd2TidsMutex;
    //std::map<int,int> fd2Tids;
    int tid2fds[128];
    int mThreadnum;
    
    ThreadPoolExecutor mExecutors;
    ArrayList<HttpDispatchRunnable> mRunnables;
};


DECLARE_SIMPLE_CLASS(HttpV1Server) IMPLEMENTS(SocketListener) {

public:
    friend class _HttpV1SocketListener;
    
    _HttpV1Server(int port,HttpV1Listener,String certificate,String key);

    _HttpV1Server(int port,HttpV1Listener);

    _HttpV1Server(HttpV1Listener);

    _HttpV1Server(HttpV1Listener,String certificate,String key);

    _HttpV1Server(String ip,int port,HttpV1Listener);

    _HttpV1Server(String ip,int port,HttpV1Listener,String certificate,String key);

    void deMonitor(int fd);
    
    void exit();

private:

    void onDataReceived(SocketResponser r,ByteArray pack);

    void onDisconnect(SocketResponser r);

    void onConnect(SocketResponser r);

    void onTimeout();

    TcpServer mTcpServer;

    SSLServer mSSLServer;

    HttpV1Listener mHttpListener;

    String mIp;

    int mPort;

    HttpDispatcherPool mPool;
};

}
#endif
