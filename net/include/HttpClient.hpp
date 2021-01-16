#ifndef __OBOTCHA_HTTP_CLIENT_HPP__
#define __OBOTCHA_HTTP_CLIENT_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HashMap.hpp"
#include "HttpCookie.hpp"
#include "TcpClient.hpp"
#include "HttpUrl.hpp"
#include "HttpResponseParser.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpClient) {

public:
    _HttpClient();
    
    void setTimeout(int timeout);

    void setKeepAlive(bool keepalive);
    
    bool isKeepAlive();

    HttpResponse execute(HttpRequest request);

private:
    String mIp;

    String mUrl;

    String mHost;
    
    int mPort;
    
    int mTimeout;
    
    bool mKeepAlive; 

    TcpClient mTcpClient;

    HttpResponseParser mParser;
};

}
#endif
