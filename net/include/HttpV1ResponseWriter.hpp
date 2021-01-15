#ifndef __OBOTCHA_HTTP_V1_RESPONSE_WRITER_HPP__
#define __OBOTCHA_HTTP_V1_RESPONSE_WRITER_HPP__

#include "HttpPacket.hpp"
#include "HttpV1ClientInfo.hpp"
#include "HttpResponse.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpV1ResponseWriter) {
public:
    _HttpV1ResponseWriter(HttpV1ClientInfo client);
    
    _HttpV1ResponseWriter();

    void disableResponse();

    bool isResponsible();
    
    int write(HttpResponse,bool flush = true);

    ByteArray compose(HttpResponse);

private:
    int mFd;

    HttpV1ClientInfo mClient;

    bool mResponsible;

    ByteArray mSendBuff;

    long computeContentLength(HttpResponse);

    int send(int);
};

}

#endif
