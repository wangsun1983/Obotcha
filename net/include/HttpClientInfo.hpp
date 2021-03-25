#ifndef __OBOTCHA_HTTP__CLIENT_INFO_HPP__
#define __OBOTCHA_HTTP__CLIENT_INFO_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HashMap.hpp"
#include "HttpCookie.hpp"
#include "HttpUrl.hpp"
#include "HttpHeader.hpp"
#include "ByteRingArray.hpp"
#include "ByteRingArrayReader.hpp"
#include "HttpPacket.hpp"
#include "SSLInfo.hpp"
#include "Random.hpp"
#include "Socket.hpp"
#include "HttpSession.hpp"
#include "HttpPacketParser.hpp"

namespace obotcha {

class _HttpServer;

DECLARE_SIMPLE_CLASS(HttpClientInfo){
public:
    friend class _HttpServer;

    _HttpClientInfo(Socket);

    int pushHttpData(ByteArray array);

    int send(ByteArray);

    int send(ByteArray,int);

    ArrayList<HttpPacket> pollHttpPacket();

    SSLInfo getSSLInfo();

    String getClientIp();

    void close();

    HttpSession getSession();

    Socket getSocket();

private:
    void setSSLInfo(SSLInfo);

    //HttpRequestParser mParser;
    HttpPacketParser mParser;

    int mStatus;

    SSLInfo mSSLInfo;

    Socket mSocket;
    OutputStream mSocketOutput;

    HttpSession mSession;
};

}
#endif
