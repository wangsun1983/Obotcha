#ifndef __OBOTCHA_HTTP_REQUEST_WRITER_HPP__
#define __OBOTCHA_HTTP_REQUEST_WRITER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "HttpPacket.hpp"
#include "HttpUrl.hpp"
#include "TcpClient.hpp"
#include "HttpRequest.hpp"
#include "ByteArrayWriter.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpRequestWriter) {

public:
    _HttpRequestWriter(TcpClient);

    _HttpRequestWriter();
    
    int write(HttpRequest);

    ByteArray compose(HttpRequest);

private:
    TcpClient mTcpClient;
    String generateMultiPartBoundary();
    ByteArray mSendBuff;
    ByteArrayWriter mBuffWriter;

    int flush(int size);
    int flush(ByteArray);

    long computeContentLength(HttpRequest,String boundary = nullptr);
};

}

#endif
