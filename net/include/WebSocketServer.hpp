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
#include "HttpV1Parser.hpp"
#include "WebSocketParser.hpp"
#include "TcpServer.hpp"
#include "WebSocketClientInfo.hpp"
#include "BlockingLinkedList.hpp"
#include "LinkedList.hpp"
#include "ThreadPoolExecutor.hpp"
#include "HttpV1Server.hpp"
#include "Random.hpp"

namespace obotcha {

class _WebSocketDispatcherPool;
class _WebSocketServer;

DECLARE_SIMPLE_CLASS(WebSocketClientManager) {
public:
    static WebSocketClientManager getInstance();
    
    WebSocketClientInfo addClient(int fd,int version);

    WebSocketClientInfo getClient(int fd);
  
    void removeClient(WebSocketClientInfo);

    uint32_t genRandomUint32();

private:
   static WebSocketClientManager mInstance;
   
   static Mutex mMutex;
   
   HashMap<int,WebSocketClientInfo> mClients;

   _WebSocketClientManager();

   Random mRand;

};

//-----------WebSocketDispatchData----------------
DECLARE_SIMPLE_CLASS(DispatchData) {
public:
    _DispatchData(uint64_t,int,int,uint32_t,ByteArray);
    _DispatchData(int,int,uint32_t,HttpPacket);
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

//---------------WebSocketDispatchRunnable------------------------
DECLARE_SIMPLE_CLASS(WebSocketDispatchRunnable) IMPLEMENTS(Runnable) {
public:
    _WebSocketDispatchRunnable(int index,sp<_WebSocketDispatcherPool>);
    void run();
    void addDefferedTask(DispatchData);
    void release();

private:
    Mutex mPoolMutex;
    int mIndex;

    sp<_WebSocketDispatcherPool> mPool;

    void handleWsData(DispatchData data);
    void handleHttpData(DispatchData data);

    HttpV1Parser mParser;
};

//------------------WebSocketDefferedTasks---------------------------
DECLARE_SIMPLE_CLASS(WebSocketDefferedTasks) {
public:
    _WebSocketDefferedTasks();

    bool isDoDefferedTask;
    Mutex mutex;
    LinkedList<DispatchData> tasks;
};

//------------------------WebSocketServer-------------------------
DECLARE_SIMPLE_CLASS(WebSocketDispatcherPool) {
public:
    friend class _WebSocketDispatchRunnable;

    _WebSocketDispatcherPool(int threadnum = 4);
    void addData(DispatchData);

    DispatchData getData(int);

    void setHttpV1Server(HttpV1Server);
    HttpV1Server getHttpV1Server();

    void setWebSocketServer(sp<_WebSocketServer>);
    sp<_WebSocketServer> getWebSocketServer();

    void release();

private:
    void clearFds(int index);
    
    Mutex mDataMutex;
    Condition mDataCondition;
    LinkedList<DispatchData> datas;
    ThreadPoolExecutor mExecutor;
    ArrayList<WebSocketDispatchRunnable> mRunnables;
    ArrayList<WebSocketDefferedTasks> mDefferedTasks;

    HttpV1Server mHttpServer;

    sp<_WebSocketServer> mWebSocketServer;

    Mutex fd2TidsMutex;
    //std::map<int,int> fd2Tids;
    int tid2fds[128];

    int mThreadnum;
};

//------------------------WebSocketServer-------------------------
DECLARE_SIMPLE_CLASS(WebSocketServer) EXTENDS(EPollFileObserverListener),st(HttpV1Listener){
public:
    friend class _WebSocketDispatchRunnable;

    _WebSocketServer();

    int bind(String ip,int port,String path,WebSocketListener listener);
    
    int bind(int port,String path,WebSocketListener listener);
    
    int start();

    int release();
    
    //WebSocket Epoll listener
    int onEvent(int fd,uint32_t events,ByteArray);

    void onMessage(sp<_HttpV1ClientInfo> client,sp<_HttpV1ResponseWriter> w,HttpPacket msg);
    void onConnect(sp<_HttpV1ClientInfo>);
    void onDisconnect(sp<_HttpV1ClientInfo>);

private:
    void monitor(int fd);

    int notifyMessage(sp<_WebSocketClientInfo> client,WebSocketFrame);

    int notifyData(sp<_WebSocketClientInfo> client,WebSocketFrame);

    int notifyConnect(sp<_WebSocketClientInfo> client);

    int notifyDisconnect(sp<_WebSocketClientInfo> client);

    int notifyPong(sp<_WebSocketClientInfo> client,String);

    int notifyPing(sp<_WebSocketClientInfo> client,String);
    
    String mPath;

    HttpV1Server mHttpServer;

    WebSocketListener mWsListener;
    
    EPollFileObserver mWsEpollObserver;

    WebSocketDispatcherPool mDispatchPool;
};


}
#endif
