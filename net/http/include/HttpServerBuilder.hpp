#ifndef __OBOTCHA_HTTP_SERVER_BUILDER_HPP__
#define __OBOTCHA_HTTP_SERVER_BUILDER_HPP__

#include "Object.hpp"
#include "HttpOption.hpp"
#include "SocketOption.hpp"
#include "Http2Listener.hpp"
#include "Http2Server.hpp"
#include "HttpServer.hpp"

namespace obotcha {

DECLARE_CLASS(HttpServerBuilder) {
  public:
    _HttpServerBuilder() = default;

    _HttpServerBuilder *setAddress(InetAddress);
    _HttpServerBuilder *setListener(HttpListener);
    _HttpServerBuilder *setOption(HttpOption);

    _HttpServerBuilder *setHttp2Listener(Http2Listener);

    HttpServer build();
    Http2Server buildHttp2Server();

  private:
    InetAddress mAddress = InetAddress::New();
    HttpOption mOption = nullptr;
    HttpListener mListener = nullptr;

    Http2Listener mHttp2Listener;
};

} // namespace obotcha

#endif