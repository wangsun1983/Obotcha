#include "SocketOption.hpp"

namespace obotcha {

const int _SocketOption::DefaultBuffSize = 4 * 1024;
const int _SocketOption::DefaultWaitAcceptQueueSize = 32 * 1024;

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

_SocketOption *_SocketOption::setReUseAddr(_SocketOption::Ability value) {
    mReUseAddr = value;
    return this;
}

_SocketOption *_SocketOption::setDnotRoute(_SocketOption::Ability on) {
    mDontRoute = on;
    return this;
}

_SocketOption *_SocketOption::setBroadcast(_SocketOption::Ability on) {
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

_SocketOption *_SocketOption::setKeepAlive(_SocketOption::Ability on) {
    mKeepAlive = on;
    return this;
}

_SocketOption *_SocketOption::setOobInline(_SocketOption::Ability on) {
    mOobInline = on;
    return this;
}

_SocketOption *_SocketOption::setNoCheck(_SocketOption::Ability on) {
    mNoCheck = on;
    return this;
}

_SocketOption *_SocketOption::setLinger(_SocketOption::Ability on, int value) {
    mLingerOnOff = on;
    mLingerValue = value;
    return this;
}

_SocketOption *_SocketOption::setReUsePort(_SocketOption::Ability on) {
    mReUsePort = on;
    return this;
}

_SocketOption *_SocketOption::setPassCred(_SocketOption::Ability on) {
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

_SocketOption *_SocketOption::setConnectTimeout(int interval) {
    mConnTimeout = interval;
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

_SocketOption *_SocketOption::setWaitAcceptQueueSize(int v) {
    mWaitAcceptQueueSize = v;
    return this;
}

_SocketOption* _SocketOption::setSSLCertificatePath(String path) {
    mSSLCertificatePath = path;
    return this;
}

_SocketOption* _SocketOption::setSSLKeyPath(String path) {
    mSSLKeyPath = path;
    return this;
}

//---------- Get Function --------------

int _SocketOption::getWaitAcceptQueueSize() const { 
    return mWaitAcceptQueueSize;
}

_SocketOption::Ability _SocketOption::getReUseAddr() const { 
    return mReUseAddr; 
}

_SocketOption::Ability _SocketOption::getDnotRoute() const { 
    return mDontRoute; 
}

_SocketOption::Ability _SocketOption::getBroadcast() const { 
    return mBroadCast; 
}

int _SocketOption::getSndBuffSize() const { 
    return mSendBuf; 
}

int _SocketOption::getRcvBuffSize() const { 
    return mRcvBuff; 
}

int _SocketOption::getSndBuffForce() const { 
    return mSendBuffForce; 
}

int _SocketOption::getRcvBuffForce() const { 
    return mRcvBuffForce; 
}

_SocketOption::Ability _SocketOption::getKeepAlive() const { 
    return mKeepAlive; 
}

_SocketOption::Ability _SocketOption::getOobInline() const { 
    return mOobInline; 
}

_SocketOption::Ability _SocketOption::getNoCheck() const { 
    return mNoCheck; 
}

_SocketOption::Ability _SocketOption::getLingerOnOFF() const { 
    return mLingerOnOff; 
}

int _SocketOption::getLingerValue() const { 
    return mLingerValue; 
}

_SocketOption::Ability _SocketOption::getReUsePort() const { 
    return mReUsePort; 
}

_SocketOption::Ability _SocketOption::getPassCred() const { 
    return mPassCred; 
}

int _SocketOption::getPeerCred() const { 
    return mPeerCred; 
}

int _SocketOption::getRcvLoWat() const { 
    return mRcvLoWat; 
}

int _SocketOption::getSndLoWat() const { 
    return mSndLoWat; 
}

int _SocketOption::getRcvTimeout() const { 
    return mRcvTimeout; 
}

int _SocketOption::getSndTimeout() const { 
    return mSendTimeout; 
}

int _SocketOption::getConnectTimeout() const { 
    return mConnTimeout; 
}

void _SocketOption::getBindToDevice(struct ifreq *v) const {
    if (mBindToDevice != nullptr) {
        memcpy(v,mBindToDevice, sizeof(struct ifreq));
    }
}

void _SocketOption::getAttachFilter(struct sock_fprog *v) const {
    if (mAttachFilter != nullptr) {
        memcpy(v,mAttachFilter,sizeof(struct sock_fprog));
    }
}

int _SocketOption::getDetachFilter() const { 
    return mDetachFilter; 
}

int _SocketOption::getTimeStamp() const { 
    return mTimeStamp; 
}

int _SocketOption::getTimeStampNs() const { 
    return mTimeStampNs; 
}

int _SocketOption::getTimeStampIng() const { 
    return mTimeStampIng; 
}

int _SocketOption::getBusyPoll() const { 
    return mBusyPoll; 
}

unsigned int _SocketOption::getMaxPacingRate() const { 
    return mMaxPacingRate; 
}

void _SocketOption::getReusePortCbpf(struct sock_fprog *v) const {
    if (mReusePortCbpf != nullptr) {
        memcpy(v, mReusePortCbpf, sizeof(struct sock_fprog));
    }
}

int _SocketOption::getReusePortEbpf() const { 
    return mReusePortEbpf; 
}

int _SocketOption::getZeroCopy() const { 
    return mZeroCopy; 
}

int _SocketOption::getRecvTimeout() const { 
    return mRcvTimeout; 
}

int _SocketOption::getSendTimeout() const { 
    return mSendTimeout; 
}

String _SocketOption::getSSLCertificatePath() const {
    return mSSLCertificatePath;
}

String _SocketOption::getSSLKeyPath() const {
    return mSSLKeyPath;
}

void _SocketOption::update(FileDescriptor fd) {
    int sock = fd->getFd();

    if (mReUseAddr != _SocketOption::Ability::UnKnown) {
        int value = static_cast<int>(mReUseAddr);
        ::setsockopt(sock,SOL_SOCKET, SO_REUSEADDR, &value,
                            sizeof(value));
    }

    if (mDontRoute != _SocketOption::Ability::UnKnown) {
        int value = static_cast<int>(mDontRoute);
        ::setsockopt(sock,SOL_SOCKET, SO_DONTROUTE, &value,
                            sizeof(value));
    }

    if (mBroadCast != _SocketOption::Ability::UnKnown) {
        int value = static_cast<int>(mBroadCast);
        ::setsockopt(sock,SOL_SOCKET, SO_BROADCAST, &value,
                            sizeof(value));
    }

    if (mSendBuf != -1) {
        ::setsockopt(sock,SOL_SOCKET, SO_SNDBUF, &mSendBuf,
                            sizeof(mSendBuf));
    }

    if (mRcvBuff != -1) {
        ::setsockopt(sock,SOL_SOCKET, SO_RCVBUF, &mRcvBuff,
                            sizeof(mRcvBuff));
    }

    if (mSendBuffForce != -1) {
        ::setsockopt(sock,SOL_SOCKET, SO_SNDBUFFORCE,
                            &mSendBuffForce,
                            sizeof(mSendBuffForce));
    }

    if (mRcvBuffForce != -1) {
        ::setsockopt(sock,SOL_SOCKET, SO_RCVBUFFORCE,
                            &mRcvBuffForce,
                            sizeof(mRcvBuffForce));
    }

    if (mKeepAlive != _SocketOption::Ability::UnKnown) {
        int value = static_cast<int>(mKeepAlive);
        ::setsockopt(sock,SOL_SOCKET, SO_KEEPALIVE, &value,
                            sizeof(value));
    }

    if (mOobInline != _SocketOption::Ability::UnKnown) {
        int value = static_cast<int>(mOobInline);
        ::setsockopt(sock,SOL_SOCKET, SO_OOBINLINE, &value,
                            sizeof(value));
    }

    if (mNoCheck != _SocketOption::Ability::UnKnown) {
        int value = static_cast<int>(mOobInline);
        ::setsockopt(sock,SOL_SOCKET, SO_NO_CHECK, &value,
                            sizeof(value));
    }

    if (mPriority != -1) {
        ::setsockopt(sock,SOL_SOCKET, SO_PRIORITY, &mPriority,
                            sizeof(mPriority));
    }

    if (mLingerOnOff != _SocketOption::Ability::UnKnown && mLingerValue != -1) {
        struct linger ll;
        ll.l_onoff = static_cast<int>(mLingerOnOff);
        ll.l_linger = mLingerValue;

        ::setsockopt(sock,SOL_SOCKET, SO_LINGER, &ll,
                            sizeof(struct linger));
    }

    if (mReUsePort != _SocketOption::Ability::UnKnown) {
        int value = static_cast<int>(mReUsePort);
        ::setsockopt(sock,SOL_SOCKET, SO_REUSEPORT, &value,
                            sizeof(value));
    }

    if (mPassCred != _SocketOption::Ability::UnKnown) {
        int value = static_cast<int>(mPassCred);
        ::setsockopt(sock,SOL_SOCKET, SO_PASSCRED, &value,
                            sizeof(value));
    }

    if (mPeerCred != -1) {
        ::setsockopt(sock,SOL_SOCKET, SO_PEERCRED, &mPeerCred,
                            sizeof(mPeerCred));
    }

    if (mRcvLoWat != -1) {
        ::setsockopt(sock,SOL_SOCKET, SO_RCVLOWAT, &mRcvLoWat,
                            sizeof(mRcvLoWat));
    }

    if (mSndLoWat != -1) {
        ::setsockopt(sock,SOL_SOCKET, SO_SNDLOWAT, &mSndLoWat,
                            sizeof(mSndLoWat));
    }

    if (mRcvTimeout != -1) {
        timeval tv;
        tv.tv_sec = mRcvTimeout / 1000;
        tv.tv_usec = (mRcvTimeout % 1000) * 1000;
        ::setsockopt(sock,SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    }

    if (mSendTimeout != -1) {
        timeval tv;
        tv.tv_sec = mSendTimeout / 1000;
        tv.tv_usec = (mSendTimeout % 1000) * 1000;
        ::setsockopt(sock,SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));
    }

    if (mBindToDevice != nullptr) {
        ::setsockopt(sock,SOL_SOCKET, SO_BINDTODEVICE,
                            mBindToDevice, sizeof(struct ifreq));
    }

    if (mAttachFilter != nullptr) {
        ::setsockopt(sock,SOL_SOCKET, SO_ATTACH_FILTER,
                            &mAttachFilter,
                            sizeof(struct sock_fprog));
    }

    if (mDetachFilter != -1) {
        ::setsockopt(sock,SOL_SOCKET, SO_DETACH_FILTER,
                            &mDetachFilter,
                            sizeof(mDetachFilter));
    }

    if (mTimeStamp != -1) {
        ::setsockopt(sock,SOL_SOCKET, SO_TIMESTAMP, &mTimeStamp,
                            sizeof(mTimeStamp));
    }

    if (mTimeStampNs != -1) {
        ::setsockopt(sock,SOL_SOCKET, SO_TIMESTAMPNS,
                            &mTimeStampNs,
                            sizeof(mTimeStampNs));
    }

    if (mTimeStampIng != -1) {
        ::setsockopt(sock,SOL_SOCKET, SO_TIMESTAMPING,
                            &mTimeStampIng,
                            sizeof(mTimeStampIng));
    }

    if (mBusyPoll != -1) {
        ::setsockopt(sock,SOL_SOCKET, SO_BUSY_POLL, &mBusyPoll,
                            sizeof(mBusyPoll));
    }

    if (mMaxPacingRate != -1) {
        ::setsockopt(sock,SOL_SOCKET, SO_MAX_PACING_RATE,
                            &mMaxPacingRate,
                            sizeof(mMaxPacingRate));
    }
#ifdef SO_ATTACH_REUSEPORT_CBPF
    if (mReusePortCbpf != nullptr) {
        ::setsockopt(sock,SOL_SOCKET, SO_ATTACH_REUSEPORT_CBPF,
                            mReusePortCbpf,
                            sizeof(struct sock_fprog));
    }
#endif

#ifdef SO_ATTACH_REUSEPORT_EBPF
    if (mReusePortEbpf != -1) {
        ::setsockopt(sock,SOL_SOCKET, SO_ATTACH_REUSEPORT_EBPF,
                            &mReusePortEbpf,
                            sizeof(mReusePortEbpf));
    }
#endif

#ifdef SO_ZEROCOPY
    if (mZeroCopy != -1) {
        ::setsockopt(sock,SOL_SOCKET, SO_ZEROCOPY, &mZeroCopy,
                            sizeof(mZeroCopy));
    }
#endif
}

int _SocketOption::get(FileDescriptor fd,
                       int level, 
                       int optname, 
                       void *optval,
                       socklen_t *oplen) {
    return ::getsockopt(fd->getFd(), level, optname, optval, oplen);
}

} // namespace obotcha
