#ifndef __OBOTCHA_HTTP_CLIENT_HPP__
#define __OBOTCHA_HTTP_CLIENT_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "HttpResponse.hpp"
#include "HttpRequest.hpp"
#include "HttpConnection.hpp"
#include "InetAddress.hpp"
#include "HttpClientConnManager.hpp"
#include "HttpClientBaseRequest.hpp"

namespace obotcha {

DECLARE_CLASS(HttpClient) {

public:
    _HttpClient();
    ~_HttpClient();
    HttpResponse execute(HttpClientBaseRequest,HttpOption = nullptr);

private:
    HttpUrl mCurrentUrl;
    static HttpClientConnManager connMgr;
};

}

#endif