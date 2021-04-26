#include "SocketOption.hpp"

namespace obotcha {

_SocketOption::_SocketOption() {
    mRcvTimeout = -1;
    mSendTimeout = -1;
    mConnectNum = 20;
}

_SocketOption* _SocketOption::setRecvTimeout(int v) {
    this->mRcvTimeout = v;
    return this;
}

_SocketOption* _SocketOption::setSendTimeout(int v) {
    this->mSendTimeout = v;
    return this;
}

_SocketOption* _SocketOption::setConnectionNum(int v) {
    mConnectNum = v;
    return this;
}

_SocketOption* _SocketOption::setBuffSize(int s) {
    mBuffSize = s;
    return this;
}

int _SocketOption::getRcvTimeout() {
    return mRcvTimeout;
}

int _SocketOption::getSendTimeout() {
    return mSendTimeout;
}

int _SocketOption::getConnectionNum() {
    return mConnectNum;
}

int _SocketOption::getBuffSize() {
    return mBuffSize;
}

}

