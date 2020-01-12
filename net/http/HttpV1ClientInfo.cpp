#include "HttpV1ClientInfo.hpp"

namespace obotcha {

_HttpV1ClientInfo::_HttpV1ClientInfo(int buffsize) {
    mStatus = HttpClientParseStatusIdle;
    mHttpHeader = createHttpHeader();
    mParseBuff = createByteArray(buffsize);
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

//HttpHeader
HttpHeader _HttpV1ClientInfo::getCurrentHttpHeader() {
    return mHttpHeader;
}

int _HttpV1ClientInfo::getParseStatus() {
    return mStatus;
}

void _HttpV1ClientInfo::updateParseStatus(HttpClientParseStatus s) {
    mStatus = s;
}

}