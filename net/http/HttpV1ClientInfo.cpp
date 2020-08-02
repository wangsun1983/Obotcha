#include "HttpV1ClientInfo.hpp"
#include "HttpPacket.hpp"
#include "NetUtils.hpp"

namespace obotcha {

_HttpV1ClientInfo::_HttpV1ClientInfo() {
    mV1Parser = createHttpV1Parser();
    mResponseWriteMutex = createMutex("HttpResponseMutex");
}

int _HttpV1ClientInfo::getClientFd() {
    return mClientFd;
}

void _HttpV1ClientInfo::setClientFd(int fd) {
    mClientFd = fd;
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
    
    return st(NetUtils)::sendTcpPacket(mClientFd,data);
}

SSLInfo _HttpV1ClientInfo::getSSLInfo() {
    return mSSLInfo;
}

void _HttpV1ClientInfo::setSSLInfo(SSLInfo info) {
    mSSLInfo = info;
}

bool _HttpV1ClientInfo::isIdle() {
    return mV1Parser->isIdle();
}

}