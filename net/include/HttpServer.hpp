#ifndef __OBOTCHA_HTTP__SERVER_HPP__
#define __OBOTCHA_HTTP__SERVER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
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
#include "HttpListener.hpp"
#include "HttpOption.hpp"

namespace obotcha {

class _HttpClientInfo;
class _HttpResponseWriter;

DECLARE_SIMPLE_CLASS(HttpServer) IMPLEMENTS(SocketListener) {

public:
    friend class _HttpSocketListener;
    
    _HttpServer(InetAddress addr,HttpListener,HttpOption option = nullptr);

    void start();
    
    void deMonitor(Socket);
    
    void exit();
    
    ~_HttpServer();

private:

    void onSocketMessage(int,Socket,ByteArray);

    ServerSocket mServerSock;

    SocketMonitor mSockMonitor;

    SSLServer mSSLServer;

    HttpListener mHttpListener;

    InetAddress mAddress;

    HttpOption mOption;
};

}
#endif
