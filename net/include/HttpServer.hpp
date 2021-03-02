#ifndef __OBOTCHA_HTTP__SERVER_HPP__
#define __OBOTCHA_HTTP__SERVER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HashMap.hpp"
#include "HttpCookie.hpp"
#include "HttpUrl.hpp"
#include "Mutex.hpp"
#include "SocketListener.hpp"
#include "HttpMultiPart.hpp"
#include "SSLServer.hpp"
#include "BlockingLinkedList.hpp"
#include "HashSet.hpp"
#include "ThreadPoolExecutor.hpp"
#include "HttpPacket.hpp"
#include "Mutex.hpp"
#include "ServerSocket.hpp"
#include "SocketMonitor.hpp"

namespace obotcha {

class _HttpClientInfo;
class _HttpResponseWriter;
class _HttpDispatcherPool;
class _HttpServer;

DECLARE_SIMPLE_CLASS(HttpTaskData) {
public:
    _HttpTaskData(int,ByteArray,uint64_t);

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

DECLARE_SIMPLE_CLASS(HttpDispatcherPool) {
public:
    _HttpDispatcherPool(sp<_HttpServer> server,int threadNum = 4);
    void release();
    HttpTaskData getData(int);
    void addData(HttpTaskData);
    void clearFds(int index);

private:
    int getGroupIdByFd(int fd);
    Mutex mDataMutex;
    Condition mDataCondition;
    mutable volatile bool isStop;

    ArrayList<LinkedList<HttpTaskData>> mTaskGroup;
    LinkedList<HttpTaskData> datas;

    //Mutex fd2TidsMutex;
    //std::map<int,int> fd2Tids;
    int GroupIdTofds[128];    
    ThreadPoolExecutor mExecutors;    
};


DECLARE_SIMPLE_CLASS(HttpServer) IMPLEMENTS(SocketListener) {

public:
    friend class _HttpSocketListener;
    friend class _HttpDispatcherPool;
    
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

    ServerSocket mServerSock;
    SocketMonitor mSockMonitor;

    SSLServer mSSLServer;

    HttpListener mHttpListener;

    String mIp;

    int mPort;

    HttpDispatcherPool mPool;

    long mSendTimeout;
    long mRcvTimeout;

    String mCertificate;
    String mKey;
};

}
#endif
