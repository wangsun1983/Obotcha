#ifndef __OBOTCHA_WEBSOCKET_SERVER_HPP__
#define __OBOTCHA_WEBSOCKET_SERVER_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <netinet/in.h>
#include <mqueue.h>
#include <fstream>
#include <sys/un.h>
#include <unordered_set>


#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "SocketListener.hpp"
#include "Mutex.hpp"
#include "Pipe.hpp"
#include "AtomicInteger.hpp"
#include "Thread.hpp"
#include "WebSocketListener.hpp"
#include "SocketListener.hpp"
#include "EPollFileObserver.hpp"
#include "Mutex.hpp"
#include "HttpV1Parser.hpp"
#include "WebSocketFrameComposer.hpp"
#include "WebSocketParser.hpp"
#include "HashMap.hpp"
#include "TcpServer.hpp"
#include "WebSocketClientInfo.hpp"
#include "CachePool.hpp"

namespace obotcha {

#define WEBSOCKET_BUFF_SIZE 512*1024

class _TcpServer; 
class _WebSocketEpollListener;
class _DispatchManager;

DECLARE_SIMPLE_CLASS(WebSocketClientManager) {
public:
    static WebSocketClientManager getInstance();
    
    bool addClient(int fd,int version);

    WebSocketClientInfo getClient(int fd);

    void setHttpHeader(int fd,HttpHeader h);

    void setWebSocketHeader(int fd,WebSocketHeader h);

    void setWebSocketPermessageDeflate(int fd,WebSocketPermessageDeflate v);

    void setWebSocketProtocols(int fd,ArrayList<String>);
    
    void removeClient(WebSocketClientInfo);

private:
   static WebSocketClientManager mInstance;
   
   static Mutex mMutex;
   
   HashMap<int,WebSocketClientInfo> mClients;

   _WebSocketClientManager();

};

DECLARE_SIMPLE_CLASS(WebSocketHttpListener) IMPLEMENTS(SocketListener){
public:
    _WebSocketHttpListener();

    void setHttpEpollObserver(EPollFileObserver);

    void setWsEpollObserver(HashMap<String,EPollFileObserver>,sp<_WebSocketEpollListener>);

    void onAccept(int fd,String ip,int port,ByteArray pack);

    void onDisconnect(int fd);

    void onConnect(int fd,String ip,int port);

    void onConnect(int fd,String domain);

    void onTimeout();

private:
    int httpEpollfd;

    HashMap<String,EPollFileObserver> mWsObservers;
    sp<_WebSocketEpollListener> mEpollListener;
    
    
    EPollFileObserver mServerObserver;
    sp<_DispatchManager> mDispatchMgr;
};

//-----------WebSocketDispatchData----------------
DECLARE_SIMPLE_CLASS(DispatchData) {
public:
    _DispatchData(int,int,uint32_t,ByteArray);
    static const int Http;
    static const int Ws;
    
    int cmd;

    int fd;
    uint32_t events;
    ByteArray data;

    //just for http
    EPollFileObserver mServerObserver;
    HashMap<String,EPollFileObserver> mWsObservers;
    sp<_WebSocketEpollListener> mEpollListener;

    //just for ws
    WebSocketListener mWsSocketListener;
};

DECLARE_SIMPLE_CLASS(DispatchStatusListener) {
public:
    virtual void onComplete(int fd) = 0;
};

DECLARE_SIMPLE_CLASS(WebSocketDispatchThread) IMPLEMENTS(Thread) {
public:
    _WebSocketDispatchThread(DispatchStatusListener);
    void add(DispatchData);
    int getWorkQueueSize();
    void run();

private:
    BlockingQueue<DispatchData> datas;
    //WebSocketListener mWsSocketListener;
    DispatchStatusListener mStatusListener;
    WebSocketFrameComposer mResponse;
    
    HttpV1Parser mParser;
    
    HashMap<int,int> fds;

    void handleHttpData(DispatchData);
    void handleWsData(DispatchData);
};

DECLARE_SIMPLE_CLASS(DispatchManager) IMPLEMENTS(DispatchStatusListener) {
public:
    _DispatchManager();
    void dispatch(DispatchData);
private:
    ArrayList<WebSocketDispatchThread> mThreads;
    void onComplete(int fd);
    Mutex mMutex;
    HashMap<int,Integer> fdmaps;
    int threadsNum;
};

//----------------------WebSocketEpollListener
DECLARE_SIMPLE_CLASS(WebSocketEpollListener) IMPLEMENTS(EPollFileObserverListener) {
public:
    _WebSocketEpollListener(WebSocketListener);
    int onEvent(int fd,uint32_t events,ByteArray);
    int onConnect(int fd);
    ~_WebSocketEpollListener();
private:
    WebSocketParser mHybi13Parser;
    WebSocketListener mWsSocketListener;
    //WebSocketFrameComposer mResponse;
    sp<_DispatchManager> mDispacher;
};

DECLARE_SIMPLE_CLASS(WebSocketServer) {
public:
    _WebSocketServer();

    int bind(String ip,int port,String path,WebSocketListener listener);
    
    int bind(int port,String path,WebSocketListener listener);
    
    int start();

    int release();

private:
    String mPath;

    sp<_TcpServer> mServer;
    
    WebSocketListener mWsListener;
    
    HashMap<String,EPollFileObserver> mEpollObservers;

    WebSocketEpollListener mEpollListener;

    WebSocketHttpListener mHttpListener;
    
    sp<_TcpServer> mHttpServer;
};


}
#endif
