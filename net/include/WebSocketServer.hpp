#ifndef __OBOTCHA_WEBSOCKET_SERVER_HPP__
#define __OBOTCHA_WEBSOCKET_SERVER_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <netinet/in.h>
#include <mqueue.h>
#include <fstream>
#include <sys/un.h>


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

namespace obotcha {

#define WEBSOCKET_BUFF_SIZE 512*1024

class _TcpServer; 
class _WebSocketEpollListener;   

DECLARE_SIMPLE_CLASS(WebSocketClientManager) {
public:
    static WebSocketClientManager getInstance();
    
    bool addClient(int fd,int version);

    WebSocketClientInfo getClient(int fd);

    void setHttpHeader(int fd,HttpHeader h);

    void setWebSocketHeader(int fd,WebSocketHeader h);

    void setWebSocketPermessageDeflate(int fd,WebSocketPermessageDeflate v);

    void setWebSocketProtocols(int fd,ArrayList<String>);
    
    void removeClient(int fd);

private:
   static WebSocketClientManager mInstance;
   
   static Mutex mMutex;
   
   HashMap<int,WebSocketClientInfo> mClients;

   _WebSocketClientManager();

};

DECLARE_SIMPLE_CLASS(WebSocketHttpListener) IMPLEMENTS(SocketListener){
public:
    _WebSocketHttpListener();

    void setHttpEpollFd(int fd);

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
    
    HttpV1Parser mParser;

    WebSocketFrameComposer mResponse;
};

DECLARE_SIMPLE_CLASS(WebSocketEpollListener) IMPLEMENTS(EPollFileObserverListener) {
public:
    _WebSocketEpollListener(WebSocketListener);
    int onEvent(int fd,uint32_t events,ByteArray);
    ~_WebSocketEpollListener();
private:
    WebSocketParser mHybi13Parser;
    WebSocketListener mWsSocketListener;
    WebSocketFrameComposer mResponse;
    byte *mRecvBuff;
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
