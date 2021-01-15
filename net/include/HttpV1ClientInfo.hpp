#ifndef __OBOTCHA_HTTP_V1_CLIENT_INFO_HPP__
#define __OBOTCHA_HTTP_V1_CLIENT_INFO_HPP__

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
#include "HttpV1RequestParser.hpp"
#include "HttpPacket.hpp"
#include "SSLInfo.hpp"
#include "HttpV1Server.hpp"
#include "Random.hpp"
#include "TcpServer.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpV1ClientInfo){
public:
    _HttpV1ClientInfo(TcpServerSocket);

    //ClientFd
    int getClientFd();

    //void setClientFd(int);

    String getClientIp();

    void setClientIp(String);

    int getParseStatus();

    int pushHttpData(ByteArray array);

    int send(ByteArray);

    int send(ByteArray,int);

    ArrayList<HttpPacket> pollHttpPacket();

    Mutex getResponseWriteMutex();

    SSLInfo getSSLInfo();

    void setSSLInfo(SSLInfo);

    sp<_HttpV1Listener> getHttpV1Listener();
    
    void setHttpV1Listener(sp<_HttpV1Listener>);

    uint64_t getClientId();

private:
    String mClientIp;

    int mClientFd;

    HttpV1RequestParser mV1Parser;

    int mStatus;

    Mutex mResponseWriteMutex;

    SSLInfo mSSLInfo;
    
    sp<_HttpV1Listener> mHttpV1ServerListener;

    uint64_t mClientId;

    Random mRnd;

    Condition mWaitCacheEmpty;

    TcpServerSocket mSocket;
};


}
#endif
