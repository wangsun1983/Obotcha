#ifndef __HTTP_CLIENT_HPP__
#define __HTTP_CLIENT_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HashMap.hpp"
#include "HttpCookie.hpp"

namespace obotcha {


DECLARE_SIMPLE_CLASS(HttpClient) {

public:
    _HttpClient();
    
    void setIp(String ip);

    void setUrl(String url);

    void setPort(int port);

    void setTimeout(int timeout);

    void setKeepAlive(bool keepalive);

    String getIp();

    String getUrl();

    int getPort();

    int getTimeout();

    bool getKeepAlive();

    int connect();

    int execute();

private:
    String mIp;
    String mUrl;
    int mPort;
    int mTimeout;
    bool mKeepAlive; 
};

}
#endif
