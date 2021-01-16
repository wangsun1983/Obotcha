#ifndef __OBOTCHA_HTTP__SERVER_HPP__
#define __OBOTCHA_HTTP__SERVER_HPP__

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
#include "Mutex.hpp"

namespace obotcha {

class _HttpClientInfo;
class _HttpResponseWriter;
class _HttpDispatcherPool;

DECLARE_SIMPLE_CLASS(DispatchHttpWorkData) {
public:
    _DispatchHttpWorkData(int,ByteArray,uint64_t);

    int fd;
    ByteArray pack;
    uint64_t clientid;
};

DECLARE_SIMPLE_CLASS(HttpListener) {
public:
    virtual void onMessage(sp<_HttpClientInfo> client,sp<_HttpResponseWriter> w,HttpPacket msg) = 0;
    virtual void onConnect(sp<_HttpClientInfo>) = 0;
    virtual void onDisconnect(sp<_HttpClientInfo>) = 0;
    virtual ~_HttpListener(){}
};


DECLARE_SIMPLE_CLASS(HttpDispatchRunnable) IMPLEMENTS(Runnable) {
public:
    _HttpDispatchRunnable(int index,sp<_HttpDispatcherPool>);
    void run();
    void onInterrupt();

private:
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
    int getTidByFd(int fd);
    Mutex mDataMutex;
    Condition mDataCondition;
    mutable volatile bool isStop;

    ArrayList<HttpDefferedTasks> mDefferedTasks;
    LinkedList<DispatchHttpWorkData> datas;

    //Mutex fd2TidsMutex;
    //std::map<int,int> fd2Tids;
    int tid2fds[128];
    int mThreadnum;
    
    ThreadPoolExecutor mExecutors;
    ArrayList<HttpDispatchRunnable> mRunnables;
};


DECLARE_SIMPLE_CLASS(HttpServer) IMPLEMENTS(SocketListener) {

public:
    friend class _HttpSocketListener;
    
    _HttpServer(int port,HttpListener,String certificate,String key);

    _HttpServer(int port,HttpListener);

    _HttpServer(HttpListener);

    _HttpServer(HttpListener,String certificate,String key);

    _HttpServer(String ip,int port,HttpListener);

    _HttpServer(String ip,int port,HttpListener,String certificate,String key);

    void start();
    
    void setSendTimeout(long);
    long getSendTimeout();

    void setRcvTimeout(long);
    long getRcvTimeout();

    void deMonitor(int fd);
    
    void exit();

private:

    void onDataReceived(SocketResponser r,ByteArray pack);

    void onDisconnect(SocketResponser r);

    void onConnect(SocketResponser r);

    void onTimeout();

    TcpServer mTcpServer;

    SSLServer mSSLServer;

    HttpListener mHttpListener;

    String mIp;

    int mPort;

    HttpDispatcherPool mPool;

    long mSendTimeout;
    long mRcvTimeout;
};

}
#endif
