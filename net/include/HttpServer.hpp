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
#include "BlockingLinkedList.hpp"
#include "HashSet.hpp"
#include "ThreadPoolExecutor.hpp"
#include "HttpPacket.hpp"
#include "Mutex.hpp"
#include "ServerSocket.hpp"
#include "SocketMonitor.hpp"
#include "HttpListener.hpp"
#include "HttpOption.hpp"
#include "HttpLinkerManager.hpp"

namespace obotcha {

class _HttpLinker;
class _HttpResponseWriter;

DECLARE_CLASS(HttpServer) IMPLEMENTS(SocketListener) {

public:
    friend class _HttpSocketListener;
    
    _HttpServer(InetAddress addr,HttpListener,HttpOption option = nullptr);

    void start();
    
    void deMonitor(Socket);
    
    void close();
    
    ~_HttpServer();

private:

    void onSocketMessage(int,Socket,ByteArray);

    ServerSocket mServerSock;

    SocketMonitor mSockMonitor;

    HttpListener mHttpListener;

    InetAddress mAddress;

    HttpOption mOption;

    HttpLinkerManager mLinkerManager;

};

}
#endif
