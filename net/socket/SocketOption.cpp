#include "SocketOption.hpp"

namespace obotcha {

const int _SocketOption::DefaultBuffSize = 4 * 1024;
const int _SocketOption::DefaultConnectNum = 4 * 1024;


_SocketOption::_SocketOption() {
    mReUseAddr = -1;
    mDontRoute = -1;
    mBroadCast = -1;
    mSendBuf = -1;
    mRcvBuff = -1;
    mSendBuffForce = -1;
    mRcvBuffForce = -1;
    mKeepAlive = -1;
    mOobInline = -1;
    mNoCheck = -1;
    mPriority = -1;
    mLingerOnOff = -1;
    mLingerValue = -1;
    mReUsePort = -1;
    mPassCred = -1;
    mPeerCred = -1;
    mRcvLoWat = -1;
    mSndLoWat = -1;
    mRcvTimeout = -1;
    mSendTimeout = -1;
    mBindToDevice = nullptr;
    mAttachFilter = nullptr;
    mDetachFilter = -1;
    mTimeStamp = -1;
    mTimeStampNs = -1;
    mTimeStampIng = -1;
    mBusyPoll = -1;
    mMaxPacingRate = -1;
    mReusePortCbpf = nullptr;
    mReusePortEbpf = -1;
    mZeroCopy = -1;
    mConnectNum = DefaultConnectNum;
    mBuffSize = DefaultBuffSize;
}

_SocketOption::~_SocketOption() {
    if (mBindToDevice != nullptr) {
        free(mBindToDevice);
        mBindToDevice = nullptr;
    }

    if (mAttachFilter != nullptr) {
        free(mAttachFilter);
        mAttachFilter = nullptr;
    }

    if (mReusePortCbpf != nullptr) {
        free(mReusePortCbpf);
        mReusePortCbpf = nullptr;
    }
}

_SocketOption *_SocketOption::setReUseAddr(int on) {
    mReUseAddr = on;
    return this;
}

_SocketOption *_SocketOption::setDnotRoute(int on) {
    mDontRoute = on;
    return this;
}

_SocketOption *_SocketOption::setBroadcast(int on) {
    mBroadCast = on;
    return this;
}

_SocketOption *_SocketOption::setSndBuffSize(int size) {
    mSendBuf = size;
    return this;
}

_SocketOption *_SocketOption::setRcvBuffSize(int size) {
    mRcvBuff = size;
    return this;
}

_SocketOption *_SocketOption::setSndBuffForce(int size) {
    mSendBuffForce = size;
    return this;
}

_SocketOption *_SocketOption::setRcvBuffForce(int size) {
    mRcvBuffForce = size;
    return this;
}

_SocketOption *_SocketOption::setKeepAlive(int on) {
    mKeepAlive = on;
    return this;
}

_SocketOption *_SocketOption::setOobInline(int on) {
    mOobInline = on;
    return this;
}

_SocketOption *_SocketOption::setNoCheck(int on) {
    mNoCheck = on;
    return this;
}

_SocketOption *_SocketOption::setLinger(int on, int value) {
    mLingerOnOff = on;
    mLingerValue = value;
    return this;
}

_SocketOption *_SocketOption::setReUsePort(int on) {
    mReUsePort = on;
    return this;
}

_SocketOption *_SocketOption::setPassCred(int on) {
    mPassCred = on;
    return this;
}

_SocketOption *_SocketOption::setPeerCred(int on) {
    mPeerCred = on;
    return this;
}

_SocketOption *_SocketOption::setRcvLoWat(int on) {
    mRcvLoWat = on;
    return this;
}

_SocketOption *_SocketOption::setSndLoWat(int on) {
    mSndLoWat = on;
    return this;
}

_SocketOption *_SocketOption::setRcvTimeout(int interval) {
    mRcvTimeout = interval;
    return this;
}

_SocketOption *_SocketOption::setSndTimeout(int interval) {
    mSendTimeout = interval;
    return this;
}

_SocketOption *_SocketOption::setBindToDevice(struct ifreq *value) {
    if (mBindToDevice != nullptr) {
        free(mBindToDevice);
    }

    mBindToDevice = (struct ifreq *)malloc(sizeof(struct ifreq));
    memcpy(mBindToDevice, value, sizeof(struct ifreq));
    return this;
}

_SocketOption *_SocketOption::setAttachFilter(struct sock_fprog *value) {
    if (mAttachFilter != nullptr) {
        free(mAttachFilter);
    }
    mAttachFilter = (struct sock_fprog *)malloc(sizeof(struct sock_fprog));
    memcpy(mAttachFilter, value, sizeof(struct sock_fprog));
    return this;
}

_SocketOption *_SocketOption::setDetachFilter(int v) {
    mDetachFilter = v;
    return this;
}

_SocketOption *_SocketOption::setTimeStamp(int v) {
    mTimeStamp = v;
    return this;
}

_SocketOption *_SocketOption::setTimeStampNs(int v) {
    mTimeStampNs = v;
    return this;
}

_SocketOption *_SocketOption::setTimeStampIng(int v) {
    mTimeStampIng = v;
    return this;
}

_SocketOption *_SocketOption::setBusyPoll(int v) {
    mBusyPoll = v;
    return this;
}

_SocketOption *_SocketOption::setMaxPacingRate(unsigned int rate) {
    mMaxPacingRate = rate;
    return this;
}

_SocketOption *_SocketOption::setReusePortCbpf(struct sock_fprog *v) {
    if (mReusePortCbpf != nullptr) {
        free(mReusePortCbpf);
    }

    mReusePortCbpf = (struct sock_fprog *)malloc(sizeof(struct sock_fprog));
    memcpy(mReusePortCbpf, v, sizeof(struct sock_fprog));
    return this;
}

_SocketOption *_SocketOption::setReusePortEbpf(int v) {
    mReusePortEbpf = v;
    return this;
}

_SocketOption *_SocketOption::setZeroCopy(int on) {
    mZeroCopy = on;
    return this;
}

_SocketOption *_SocketOption::setConnectionNum(int v) {
    mConnectNum = v;
    return this;
}

_SocketOption *_SocketOption::setBuffSize(int s) {
    mBuffSize = s;
    return this;
}

int _SocketOption::getConnectionNum() { return mConnectNum; }

int _SocketOption::getReUseAddr() { return mReUseAddr; }

int _SocketOption::getDnotRoute() { return mDontRoute; }

int _SocketOption::getBroadcast() { return mBroadCast; }

int _SocketOption::getSndBuffSize() { return mSendBuf; }

int _SocketOption::getRcvBuffSize() { return mRcvBuff; }

int _SocketOption::getSndBuffForce() { return mSendBuffForce; }

int _SocketOption::getRcvBuffForce() { return mRcvBuffForce; }

int _SocketOption::getKeepAlive() { return mKeepAlive; }

int _SocketOption::getOobInline() { return mOobInline; }

int _SocketOption::getNoCheck() { return mNoCheck; }

int _SocketOption::getLingerOnOFF() { return mLingerOnOff; }

int _SocketOption::getLingerValue() { return mLingerValue; }

int _SocketOption::getReUsePort() { return mReUsePort; }

int _SocketOption::getPassCred() { return mPassCred; }

int _SocketOption::getPeerCred() { return mPeerCred; }

int _SocketOption::getRcvLoWat() { return mRcvLoWat; }

int _SocketOption::getSndLoWat() { return mSndLoWat; }

int _SocketOption::getRcvTimeout() { return mRcvTimeout; }

int _SocketOption::getSndTimeout() { return mSendTimeout; }

void _SocketOption::getBindToDevice(struct ifreq *v) {
    if (mBindToDevice != nullptr) {
        memcpy(mBindToDevice, v, sizeof(struct ifreq));
    }
}

void _SocketOption::getAttachFilter(struct sock_fprog *v) {
    if (mAttachFilter != nullptr) {
        memcpy(mAttachFilter, v, sizeof(struct sock_fprog));
    }
}

int _SocketOption::getDetachFilter() { return mDetachFilter; }

int _SocketOption::getTimeStamp() { return mTimeStamp; }

int _SocketOption::getTimeStampNs() { return mTimeStampNs; }

int _SocketOption::getTimeStampIng() { return mTimeStampIng; }

int _SocketOption::getBusyPoll() { return mBusyPoll; }

unsigned int _SocketOption::getMaxPacingRate() { return mMaxPacingRate; }

void _SocketOption::getReusePortCbpf(struct sock_fprog *v) {
    if (mReusePortCbpf != nullptr) {
        memcpy(v, mReusePortCbpf, sizeof(struct sock_fprog));
    }
}

int _SocketOption::getReusePortEbpf() { 
    return mReusePortEbpf; 
}

int _SocketOption::getZeroCopy() { return mZeroCopy; }

int _SocketOption::getRecvTimeout() { return mRcvTimeout; }

int _SocketOption::getSendTimeout() { return mSendTimeout; }

int _SocketOption::getBuffSize() { return mBuffSize; }

} // namespace obotcha
