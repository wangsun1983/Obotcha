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

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpClientInfo){
public:
    _HttpClientInfo(TcpServerSocket);

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

    sp<_HttpListener> getHttpListener();
    
    void setHttpListener(sp<_HttpListener>);

    uint64_t getClientId();

private:
    String mClientIp;

    int mClientFd;

    HttpRequestParser mParser;

    int mStatus;

    Mutex mResponseWriteMutex;

    SSLInfo mSSLInfo;
    
    sp<_HttpListener> mHttpServerListener;

    uint64_t mClientId;

    Random mRnd;

    Condition mWaitCacheEmpty;

    TcpServerSocket mSocket;
};


}
#endif
