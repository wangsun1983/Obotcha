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
#include "ByteRingArray.hpp"
#include "ByteRingArrayReader.hpp"
#include "HttpV1Parser.hpp"
#include "HttpPacket.hpp"
#include "SSLInfo.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpV1ClientInfo){
public:
    _HttpV1ClientInfo();

    //ClientFd
    int getClientFd();

    void setClientFd(int);

    String getClientIp();

    void setClientIp(String);

    int getParseStatus();

    int pushHttpData(ByteArray array);

    int send(ByteArray);

    ArrayList<HttpPacket> pollHttpPacket();

    Mutex getResponseWriteMutex();

    SSLInfo getSSLInfo();

    void setSSLInfo(SSLInfo);

private:
    String mClientIp;

    int mClientFd;

    HttpV1Parser mV1Parser;

    int mStatus;

    Mutex mResponseWriteMutex;

    SSLInfo mSSLInfo;

};


}
#endif
