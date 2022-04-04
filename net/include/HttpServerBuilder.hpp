#ifndef __OBOTCHA_HTTP_SERVER_BUILDER_HPP__
#define __OBOTCHA_HTTP_SERVER_BUILDER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ByteArray.hpp"
#include "HttpOption.hpp"
#include "HttpServer.hpp"
#include "ServerSocket.hpp"
#include "Socket.hpp"
#include "SocketOption.hpp"

#include "Http2Listener.hpp"
#include "Http2Server.hpp"

namespace obotcha {

DECLARE_CLASS(HttpServerBuilder) {
  public:
    _HttpServerBuilder();

    _HttpServerBuilder *setAddress(InetAddress);
    _HttpServerBuilder *setListener(HttpListener);
    _HttpServerBuilder *setOption(HttpOption);
    _HttpServerBuilder *setCertificatePath(String);
    _HttpServerBuilder *setKeyPath(String);
    _HttpServerBuilder *setProtocol(int);

    _HttpServerBuilder *setHttp2Listener(Http2Listener);

    HttpServer build();
    Http2Server buildHttp2Server();
    

  private:
    void updateOption();
    
    InetAddress mAddress;
    HttpOption mOption;
    HttpListener mListener;
    String mCertificatePath;
    String mKeyPath;
    int mProtocol;

    Http2Listener mHttp2Listener;
};

} // namespace obotcha

#endif