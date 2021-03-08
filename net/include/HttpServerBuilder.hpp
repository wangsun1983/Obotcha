#ifndef __OBOTCHA_HTTP_SERVER_BUILDER_HPP__
#define __OBOTCHA_HTTP_SERVER_BUILDER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ByteArray.hpp"
#include "Socket.hpp"
#include "SocketOption.hpp"
#include "ServerSocket.hpp"
#include "HttpServer.hpp"
#include "HttpOption.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpServerBuilder) {
public:
    _HttpServerBuilder();
    
    _HttpServerBuilder* setAddress(InetAddress);
    _HttpServerBuilder* setListener(HttpListener);
    _HttpServerBuilder* setOption(HttpOption);

    HttpServer build();
    
private:
    InetAddress mAddress;
    HttpOption mOption;
    HttpListener mListener;
};

}

#endif