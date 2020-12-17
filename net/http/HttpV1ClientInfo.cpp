#include "HttpV1ClientInfo.hpp"
#include "HttpPacket.hpp"
#include "HttpV1Server.hpp"
#include "HttpClientManager.hpp"

namespace obotcha {

_HttpV1ClientInfo::_HttpV1ClientInfo() {
    mV1Parser = createHttpV1Parser();
    mResponseWriteMutex = createMutex("HttpResponseMutex");
    mClientId = -1;
    //mRnd = createRandom();
}

int _HttpV1ClientInfo::getClientFd() {
    return mClientFd;
}

void _HttpV1ClientInfo::setClientFd(int fd) {
    mClientFd = fd;
    uint32_t rnd = st(HttpV1ClientManager)::getInstance()->genRandomUint32();
    mClientId = ((uint64_t)fd<<32|rnd);
}

uint64_t _HttpV1ClientInfo::getClientId() {
    return mClientId;
}

String _HttpV1ClientInfo::getClientIp() {
    return mClientIp;
}

void _HttpV1ClientInfo::setClientIp(String ip) {
    mClientIp = ip;
}

int _HttpV1ClientInfo::getParseStatus() {
    return mV1Parser->getStatus();
}


int _HttpV1ClientInfo::pushHttpData(ByteArray array) {
    mV1Parser->pushHttpData(array);
    //TODO
    return 0;
}

ArrayList<HttpPacket> _HttpV1ClientInfo::pollHttpPacket() {
    return mV1Parser->doParse();
}

Mutex _HttpV1ClientInfo::getResponseWriteMutex() {
    return mResponseWriteMutex;
}

int _HttpV1ClientInfo::send(ByteArray data) {
    if(mSSLInfo != nullptr) {
        return mSSLInfo->write(data);
    }

    fcntl(mClientFd, F_SETFL, fcntl(mClientFd, F_GETFD, 0)| O_SYNC);
    //return st(NetUtils)::sendTcpPacket(mClientFd,data);
    int result = ::send(mClientFd,data->toValue(),data->size(),0);
    fcntl(mClientFd, F_SETFL, fcntl(mClientFd, F_GETFD, 0)| O_NONBLOCK);
    return result;
}

SSLInfo _HttpV1ClientInfo::getSSLInfo() {
    return mSSLInfo;
}

void _HttpV1ClientInfo::setSSLInfo(SSLInfo info) {
    mSSLInfo = info;
}

//bool _HttpV1ClientInfo::isIdle() {
//    return mV1Parser->isIdle();
//}

HttpV1Listener _HttpV1ClientInfo::getHttpV1Listener() {
    return mHttpV1ServerListener;
}
    
void _HttpV1ClientInfo::setHttpV1Listener(HttpV1Listener v) {
    mHttpV1ServerListener = v;
}

}