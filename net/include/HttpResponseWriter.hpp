#ifndef __OBOTCHA_HTTP__RESPONSE_WRITER_HPP__
#define __OBOTCHA_HTTP__RESPONSE_WRITER_HPP__

#include "HttpPacket.hpp"
#include "HttpClientInfo.hpp"
#include "HttpResponse.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpResponseWriter) {
public:
    _HttpResponseWriter(HttpClientInfo client);
    
    _HttpResponseWriter();

    void disableResponse();

    bool isResponsible();
    
    int write(HttpResponse,bool flush = true);

    ByteArray compose(HttpResponse);

private:
    int mFd;

    HttpClientInfo mClient;

    bool mResponsible;

    ByteArray mSendBuff;

    long computeContentLength(HttpResponse);

    int send(int);
};

}

#endif