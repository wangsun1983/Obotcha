#ifndef __WEBSOCKET_SERVER_HPP__
#define __WEBSOCKET_SERVER_HPP__

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
#include "HttpParser.hpp"
#include "WebSocketFrameComposer.hpp"
#include "WebSocketParser.hpp"
#include "HashMap.hpp"
#include "TcpServer.hpp"

namespace obotcha {

class _TcpServer;    

DECLARE_SIMPLE_CLASS(WebSocketHttpListener) IMPLEMENTS(SocketListener){
public:
    _WebSocketHttpListener();

    void setHttpEpollFd(int fd);

    void setWsEpollObserver(HashMap<String,EPollFileObserver>);

    void onAccept(int fd,String ip,int port,ByteArray pack);

    void onDisconnect(int fd);

    void onConnect(int fd,String ip,int port);

    void onConnect(int fd,String domain);

    void onTimeout();

private:
    int httpEpollfd;

    HashMap<String,EPollFileObserver> mWsObservers;  
    
    HttpParser mParser;

    WebSocketFrameComposer mResponse;
};

DECLARE_SIMPLE_CLASS(WebSocketEpollListener) IMPLEMENTS(EPollFileObserverListener) {
public:
    _WebSocketEpollListener(WebSocketListener);
    int onEvent(int fd,int events);

private:
    WebSocketParser mHybi13Parser;
    WebSocketListener mWsSocketListener;
    WebSocketFrameComposer mResponse;
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
