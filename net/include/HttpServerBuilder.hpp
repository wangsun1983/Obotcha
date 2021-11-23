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

namespace obotcha {

DECLARE_CLASS(HttpServerBuilder) {
  public:
    _HttpServerBuilder();

    _HttpServerBuilder *setAddress(InetAddress);
    _HttpServerBuilder *setListener(HttpListener);
    _HttpServerBuilder *setOption(HttpOption);
    _HttpServerBuilder *setCertificatePath(String);
    _HttpServerBuilder *setKeyPath(String);

    HttpServer build();

  private:
    InetAddress mAddress;
    HttpOption mOption;
    HttpListener mListener;
    String mCertificatePath;
    String mKeyPath;
};

} // namespace obotcha

#endif