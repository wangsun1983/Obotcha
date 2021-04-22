#ifndef __OBOTCHA_HTTP_REQUEST_WRITER_HPP__
#define __OBOTCHA_HTTP_REQUEST_WRITER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "HttpPacket.hpp"
#include "HttpUrl.hpp"
#include "HttpRequest.hpp"
#include "ByteArrayWriter.hpp"
#include "Socket.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpRequestWriter) {

public:
    _HttpRequestWriter(OutputStream);

    _HttpRequestWriter();
    
    int write(HttpRequest);

    ByteArray compose(HttpRequest);

private:
    OutputStream mOutputStream;
    
    String generateMultiPartBoundary();
    ByteArray mSendBuff;
    ByteArrayWriter mBuffWriter;

    int flush(int size);
    int flush(ByteArray);
    int flush(ByteArray,int);

    long computeContentLength(HttpRequest,String boundary = nullptr);
};

}

#endif
