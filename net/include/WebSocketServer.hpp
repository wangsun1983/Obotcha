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
#include "WebSocketParser.hpp"
#include "WebSocketLinker.hpp"
#include "BlockingLinkedList.hpp"
#include "LinkedList.hpp"
#include "ThreadPoolExecutor.hpp"
#include "HttpServer.hpp"
#include "Random.hpp"
#include "SpinLock.hpp"
#include "WebSocketOption.hpp"

namespace obotcha {

//------------------------WebSocketServer-------------------------
DECLARE_SIMPLE_CLASS(WebSocketServer) IMPLEMENTS(HttpListener,SocketListener){
public:

    _WebSocketServer(InetAddress,WebSocketOption wsoption = nullptr,HttpOption httpoption = nullptr);

    int bind(String,WebSocketListener);

    int start();

    int close();

private:
    void onHttpMessage(int,sp<_HttpLinker> client,sp<_HttpResponseWriter> w,HttpPacket msg);

    void onSocketMessage(int,Socket,ByteArray);

    InetAddress mAddress;

    HttpServer mHttpServer;

    SocketMonitor mSocketMonitor;
    
    //wangsl
    Mutex mListenersLock;
    HashMap<String,WebSocketListener> mWsListeners;
    //wangsl
    WebSocketOption mWsOption;

    HttpOption mHttpOption;
    
};


}
#endif
