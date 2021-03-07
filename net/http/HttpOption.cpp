#include "HttpOption.hpp"

namespace obotcha {

_HttpOption::_HttpOption() {
    mRcvTimeout = -1;
    mSendTimeout = -1;
    mConnectNum = 20;
    mKey = nullptr;
    mCretificate = nullptr;
}

_HttpOption* _HttpOption::setRecvTimeout(int v) {
    this->mRcvTimeout = v;
    return this;
}

_HttpOption* _HttpOption::setSendTimeout(int v) {
    this->mSendTimeout = v;
    return this;
}

_HttpOption* _HttpOption::setConnectionNum(int v) {
    mConnectNum = v;
    return this;
}

_HttpOption* _HttpOption::setCertificate(String v) {
    mCretificate = v;
    return this;
}

_HttpOption* _HttpOption::setKey(String v) {
    mKey = v;
    return this;
}

int _HttpOption::getRcvTimeout() {
    return mRcvTimeout;
}

int _HttpOption::getSendTimeout() {
    return mSendTimeout;
}

int _HttpOption::getConnectionNum() {
    return mConnectNum;
}

String _HttpOption::getCertificate() {
    return mCretificate;
}

String _HttpOption::getKey() {
    return mKey;
}

}

