#ifndef __HTTP_V1_CLIENT_INFO_HPP__
#define __HTTP_V1_CLIENT_INFO_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HashMap.hpp"
#include "HttpCookie.hpp"
#include "TcpClient.hpp"
#include "HttpUrl.hpp"
#include "TcpServer.hpp"
#include "HttpHeader.hpp"

namespace obotcha {

enum HttpClientParseStatus {
    HttpClientParseStatusIdle = 0,
    HttpClientParseStatusHeadStart,
    HttpClientParseStatusBodyStart,
};

DECLARE_SIMPLE_CLASS(HttpV1ClientInfo){
public:
    _HttpV1ClientInfo(int buffsize);

    //ClientFd
    int getClientFd();

    void setClientFd(int);

    String getClientIp();

    void setClientIp(String);

    int getParseStatus();

    void updateParseStatus(HttpClientParseStatus);

    //HttpHeader
    HttpHeader getCurrentHttpHeader();

private:
    String mClientIp;

    int mClientFd;

    HttpClientParseStatus mStatus;
    
    HttpHeader mHttpHeader;

    ByteArray mParseBuff;
};


}
#endif
