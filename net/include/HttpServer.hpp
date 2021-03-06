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
#include "HttpListener.hpp"

namespace obotcha {

class _HttpClientInfo;
class _HttpResponseWriter;

DECLARE_SIMPLE_CLASS(HttpServer) IMPLEMENTS(SocketListener) {

public:
    friend class _HttpSocketListener;
    friend class _HttpDispatcherPool;
    
    _HttpServer(InetAddress addr,HttpListener,String certificate,String key);

    void start();
    
    void setSendTimeout(long);
    
    long getSendTimeout();

    void setRcvTimeout(long);
    long getRcvTimeout();

    void deMonitor(Socket);
    
    void exit();

private:

    void onSocketMessage(int,Socket,ByteArray);

    ServerSocket mServerSock;
    SocketMonitor mSockMonitor;

    SSLServer mSSLServer;

    HttpListener mHttpListener;

    String mIp;

    int mPort;

    long mSendTimeout;
    long mRcvTimeout;

    String mCertificate;
    String mKey;

    InetAddress mAddress;
};

}
#endif
