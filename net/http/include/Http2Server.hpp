#ifndef __OBOTCHA_HTTP_V2_SERVER_HPP__
#define __OBOTCHA_HTTP_V2_SERVER_HPP__

#include "Object.hpp"
#include "SocketListener.hpp"
#include "ServerSocket.hpp"
#include "SocketMonitor.hpp"
#include "HttpListener.hpp"
#include "HttpOption.hpp"
#include "Http2Listener.hpp"
#include "ConcurrentHashMap.hpp"

namespace obotcha {

DECLARE_CLASS(Http2Server) IMPLEMENTS(SocketListener) {

public:
    friend class _HttpSocketListener;
    
    _Http2Server(InetAddress addr,Http2Listener,HttpOption option = nullptr);

    void start();
    
    void close();
    
    ~_Http2Server();

private:
    void onSocketMessage(int,Socket,ByteArray);
    
    ServerSocket mServerSock;

    SocketMonitor mSockMonitor;

    Http2Listener mHttpListener;

    InetAddress mAddress;

    HttpOption mOption;

    ConcurrentHashMap<Socket,HttpLinker> mLinkers;
};

}
#endif
