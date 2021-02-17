#include "HttpClientInfo.hpp"
#include "HttpPacket.hpp"
#include "HttpServer.hpp"
#include "HttpClientManager.hpp"

namespace obotcha {

_HttpClientInfo::_HttpClientInfo(Socket s) {
    mParser = createHttpRequestParser();
    mClientFd = s->getFd();
    mSocket = s;
    uint32_t rnd = st(HttpClientManager)::getInstance()->genRandomUint32();
    mClientId = ((uint64_t)mClientId<<32|rnd);
    mSession = createHttpSession();
}

int _HttpClientInfo::getClientFd() {
    return mClientFd;
}

void _HttpClientInfo::close() {
    ::close(mClientFd);
    mParser = nullptr;
}

uint64_t _HttpClientInfo::getClientId() {
    return mClientId;
}

String _HttpClientInfo::getClientIp() {
    return mClientIp;
}

void _HttpClientInfo::setClientIp(String ip) {
    mClientIp = ip;
}

int _HttpClientInfo::pushHttpData(ByteArray array) {
    mParser->pushHttpData(array);
    return 0;
}

ArrayList<HttpPacket> _HttpClientInfo::pollHttpPacket() {
    return mParser->doParse();
}

int _HttpClientInfo::send(ByteArray data) {
    if(mSSLInfo != nullptr) {
        return mSSLInfo->write(data);
    }

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


}