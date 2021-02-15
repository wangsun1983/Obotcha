#ifndef __OBOTCHA_WEBSOCKET_SERVER_HPP__
#define __OBOTCHA_WEBSOCKET_SERVER_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>
#include <sys/un.h>
#include <unordered_set>
#include <map>


#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "SocketListener.hpp"
#include "Mutex.hpp"
#include "WebSocketListener.hpp"
#include "HttpPacket.hpp"
#include "EPollFileObserver.hpp"
#include "HttpRequestParser.hpp"
#include "WebSocketParser.hpp"
#include "TcpServer.hpp"
#include "WebSocketClientInfo.hpp"
#include "BlockingLinkedList.hpp"
#include "LinkedList.hpp"
#include "ThreadPoolExecutor.hpp"
#include "HttpServer.hpp"
#include "Random.hpp"
#include "SpinLock.hpp"

namespace obotcha {

class _WebSocketDispatcherPool;
class _WebSocketServer;

//-----------WebSocketDispatchData----------------
DECLARE_SIMPLE_CLASS(DispatchData) {
public:
    _DispatchData(uint64_t,int,int,uint32_t,ByteArray);
    _DispatchData(uint64_t,int,int,uint32_t,HttpPacket);

    enum DataType {
        Http = 0,
        Ws,
    };
    
    int cmd;
    int fd;
    uint64_t clientId;

    uint32_t events;
    ByteArray data;
    HttpPacket packet;
};

//------------------------WebSocketServer-------------------------
DECLARE_SIMPLE_CLASS(WebSocketDispatcherPool) {
public:
    _WebSocketDispatcherPool(int threadnum = 4);
    void addData(DispatchData);

    DispatchData getData(int);

    void setHttpServer(HttpServer);
    void setWebSocketServer(sp<_WebSocketServer>);
    
    void handleWsData(DispatchData data);
    void handleHttpData(DispatchData data);
    
    void release();

private:

    Mutex mDataMutex;
    Condition mDataCondition;
    LinkedList<DispatchData> datas;
    ThreadPoolExecutor mExecutor;
    ArrayList<LinkedList<DispatchData>> mTaskGroup;

    HttpServer mHttpServer;
    sp<_WebSocketServer> mWebSocketServer;
    
    mutable volatile bool isStop;
    int GroupIdTofds[128];

    int getGroupIdByFd(int);
};

//------------------------WebSocketServer-------------------------
DECLARE_SIMPLE_CLASS(WebSocketServer) EXTENDS(EPollFileObserverListener),st(HttpListener){
public:
    friend class _WebSocketDispatcherPool;

    _WebSocketServer();

    void setSendTimeout(long);
    long getSendTimeout();

    void setRcvTimeout(long);
    long getRcvTimeout();

    int bind(String ip,int port,String path,WebSocketListener listener);
    
    int bind(int port,String path,WebSocketListener listener);
    
    int start();

    int release();
    
    //WebSocket Epoll listener
    int onEvent(int fd,uint32_t events,ByteArray);

    void onMessage(sp<_HttpClientInfo> client,sp<_HttpResponseWriter> w,HttpPacket msg);
    void onConnect(sp<_HttpClientInfo>);
    void onDisconnect(sp<_HttpClientInfo>);

private:
    void monitor(int fd);

    int notifyMessage(sp<_WebSocketClientInfo> client,WebSocketFrame);

    int notifyData(sp<_WebSocketClientInfo> client,WebSocketFrame);

    int notifyConnect(sp<_WebSocketClientInfo> client);

    int notifyDisconnect(sp<_WebSocketClientInfo> client);

    int notifyPong(sp<_WebSocketClientInfo> client,String);

    int notifyPing(sp<_WebSocketClientInfo> client,String);
    
    String mPath;

    HttpServer mHttpServer;

    WebSocketListener mWsListener;
    
    EPollFileObserver mWsEpollObserver;

    WebSocketDispatcherPool mDispatchPool;
    
    long mSendTimeout;
    long mRcvTimeout;
};


}
#endif
