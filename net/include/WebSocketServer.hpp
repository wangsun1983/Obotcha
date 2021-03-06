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
#include "WebSocketClientInfo.hpp"
#include "BlockingLinkedList.hpp"
#include "LinkedList.hpp"
#include "ThreadPoolExecutor.hpp"
#include "HttpServer.hpp"
#include "Random.hpp"
#include "SpinLock.hpp"

namespace obotcha {

//------------------------WebSocketServer-------------------------
DECLARE_SIMPLE_CLASS(WebSocketServer) IMPLEMENTS(HttpListener),st(SocketListener){
public:

    _WebSocketServer();

    void setSendTimeout(long);
    long getSendTimeout();

    void setRcvTimeout(long);
    long getRcvTimeout();

    int bind(InetAddress mAddress,String path,WebSocketListener listener);
    
    int start();

    int release();

private:
    void onHttpMessage(int,sp<_HttpClientInfo> client,sp<_HttpResponseWriter> w,HttpPacket msg);

    void onSocketMessage(int,Socket,ByteArray);

    String mPath;

    InetAddress mAddress;

    HttpServer mHttpServer;

    SocketMonitor mSocketMonitor;

    WebSocketListener mWsListener;
    
    long mSendTimeout;
    long mRcvTimeout;
};


}
#endif
