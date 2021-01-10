#ifndef __OBOTCHA_HTTP_REQUEST_WRITER_HPP__
#define __OBOTCHA_HTTP_REQUEST_WRITER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "HttpPacket.hpp"
#include "HttpUrl.hpp"
#include "TcpClient.hpp"
#include "HttpRequest.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpRequestWriter) {

public:
    _HttpRequestWriter(TcpClient);
    int write(HttpRequest);
private:
    TcpClient mTcpClient;
    String generateMultiPartBoundary();
    
};

}

#endif
