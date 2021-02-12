#include "HttpClientInfo.hpp"
#include "HttpPacket.hpp"
#include "HttpServer.hpp"
#include "HttpClientManager.hpp"

namespace obotcha {

_HttpClientInfo::_HttpClientInfo(Socket s) {
    mParser = createHttpRequestParser();
    mResponseWriteMutex = createMutex("HttpResponseMutex");
    mClientFd = s->getFd();
    mSocket = s;
    uint32_t rnd = st(HttpClientManager)::getInstance()->genRandomUint32();
    mClientId = ((uint64_t)mClientId<<32|rnd);
    //mRnd = createRandom();
}

int _HttpClientInfo::getClientFd() {
    return mClientFd;
}

//void _HttpClientInfo::setClientFd(int fd) {
//    mClientFd = fd;
//    uint32_t rnd = st(HttpClientManager)::getInstance()->genRandomUint32();
//    mClientId = ((uint64_t)fd<<32|rnd);
//}

uint64_t _HttpClientInfo::getClientId() {
    return mClientId;
}

String _HttpClientInfo::getClientIp() {
    return mClientIp;
}

void _HttpClientInfo::setClientIp(String ip) {
    mClientIp = ip;
}

int _HttpClientInfo::getParseStatus() {
    return mParser->getStatus();
}


int _HttpClientInfo::pushHttpData(ByteArray array) {
    mParser->pushHttpData(array);
    return 0;
}

ArrayList<HttpPacket> _HttpClientInfo::pollHttpPacket() {
    return mParser->doParse();
}

Mutex _HttpClientInfo::getResponseWriteMutex() {
    return mResponseWriteMutex;
}

int _HttpClientInfo::send(ByteArray data) {
    if(mSSLInfo != nullptr) {
        return mSSLInfo->write(data);
    }

    //fcntl(mClientFd, F_SETFL, fcntl(mClientFd, F_GETFD, 0)| O_SYNC);
    //return st(NetUtils)::sendTcpPacket(mClientFd,data);
    //int result = ::send(mClientFd,data->toValue(),data->size(),0);
    //fcntl(mClientFd, F_SETFL, fcntl(mClientFd, F_GETFD, 0)| O_NONBLOCK);
    return mSocket->send(data);
}

int _HttpClientInfo::send(ByteArray data,int size) {
    if(mSSLInfo != nullptr) {
        return mSSLInfo->write(data);
    }

    return mSocket->send(data,size);
}

SSLInfo _HttpClientInfo::getSSLInfo() {
    return mSSLInfo;
}

void _HttpClientInfo::setSSLInfo(SSLInfo info) {
    mSSLInfo = info;
}

//bool _HttpClientInfo::isIdle() {
//    return mParser->isIdle();
//}

HttpListener _HttpClientInfo::getHttpListener() {
    return mHttpServerListener;
}
    
void _HttpClientInfo::setHttpListener(HttpListener v) {
    mHttpServerListener = v;
}

}