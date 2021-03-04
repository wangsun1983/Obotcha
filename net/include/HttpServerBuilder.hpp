#ifndef __OBOTCHA_HTTP_SERVER_BUILDER_HPP__
#define __OBOTCHA_HTTP_SERVER_BUILDER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ByteArray.hpp"
#include "Socket.hpp"
#include "SocketOption.hpp"
#include "ServerSocket.hpp"
#include "HttpServer.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpServerBuilder) {
public:
    _HttpServerBuilder();
    
    _HttpServerBuilder* setAddress(InetAddress);
    _HttpServerBuilder* setCertificate(String);
    _HttpServerBuilder* setKey(String);
    _HttpServerBuilder* setListener(HttpListener);
    
    HttpServer build();
    
    
private:
    InetAddress mAddress;
    String mCert;
    String mKey;
    HttpListener mListener;
};

}

#endif