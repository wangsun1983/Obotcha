#include "WebSocketOption.hpp"

namespace obotcha {

_WebSocketOption::_WebSocketOption() {
    mRcvTimeout = -1;
    mSendTimeout = -1;
    mConnectNum = 20;
}

_WebSocketOption* _WebSocketOption::setRecvTimeout(int v) {
    this->mRcvTimeout = v;
    return this;
}

_WebSocketOption* _WebSocketOption::setSendTimeout(int v) {
    this->mSendTimeout = v;
    return this;
}

_WebSocketOption* _WebSocketOption::setConnectionNum(int v) {
    mConnectNum = v;
    return this;
}

int _WebSocketOption::getRcvTimeout() {
    return mRcvTimeout;
}

int _WebSocketOption::getSendTimeout() {
    return mSendTimeout;
}

int _WebSocketOption::getConnectionNum() {
    return mConnectNum;
}


}

