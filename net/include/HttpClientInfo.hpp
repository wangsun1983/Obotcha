#ifndef __OBOTCHA_HTTP__CLIENT_INFO_HPP__
#define __OBOTCHA_HTTP__CLIENT_INFO_HPP__

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
#include "HttpRequestParser.hpp"
#include "HttpPacket.hpp"
#include "SSLInfo.hpp"
#include "HttpServer.hpp"
#include "Random.hpp"
#include "TcpServer.hpp"
#include "Socket.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpClientInfo){
public:
    friend class _HttpServer;

    _HttpClientInfo(Socket);

    int getClientFd();

    String getClientIp();

    int pushHttpData(ByteArray array);

    int send(ByteArray);

    int send(ByteArray,int);

    ArrayList<HttpPacket> pollHttpPacket();

    SSLInfo getSSLInfo();

    uint64_t getClientId();

    void close();

private:
    void setClientIp(String);
    
    void setSSLInfo(SSLInfo);

    String mClientIp;

    int mClientFd;

    HttpRequestParser mParser;

    int mStatus;

    SSLInfo mSSLInfo;
    
    sp<_HttpListener> mHttpServerListener;

    uint64_t mClientId;

    Socket mSocket;
};

}
#endif
