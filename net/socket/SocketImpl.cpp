#include "SocketImpl.hpp"

namespace obotcha {

_SocketImpl::_SocketImpl(FileDescriptor fd) {
    sock = fd;
    mBuffSize = 1024*4;
    address = nullptr;
    option = nullptr;
}

_SocketImpl::_SocketImpl(InetAddress address,SocketOption option) {
    this->address = address;
    this->option = option;
    this->mBuffSize = 4*1024;
}

void _SocketImpl::setRecvBuff(int v) {
    mBuffSize = v;
}

void _SocketImpl::setOptions() {
    if(option != nullptr) {
        if(option->mReUseAddr != -1) {
            sock->setSockOption(SOL_SOCKET, SO_REUSEADDR, &option->mReUseAddr, sizeof(option->mReUseAddr));
        }

        if(option->mDontRoute != -1) {
            sock->setSockOption(SOL_SOCKET, SO_DONTROUTE, &option->mDontRoute, sizeof(option->mDontRoute));
        }

        if(option->mBroadCast != -1) {
            sock->setSockOption(SOL_SOCKET, SO_BROADCAST, &option->mBroadCast, sizeof(option->mBroadCast));
        }

        if(option->mSendBuf != -1) {
            sock->setSockOption(SOL_SOCKET, SO_SNDBUF, &option->mSendBuf, sizeof(option->mSendBuf));
        }

        if(option->mRcvBuff != -1) {
            sock->setSockOption(SOL_SOCKET, SO_RCVBUF, &option->mRcvBuff, sizeof(option->mRcvBuff));
        }

        if(option->mSendBuffForce != -1) {
            sock->setSockOption(SOL_SOCKET, SO_SNDBUFFORCE, &option->mSendBuffForce, sizeof(option->mSendBuffForce));
        }

        if(option->mRcvBuffForce != -1) {
            sock->setSockOption(SOL_SOCKET, SO_RCVBUFFORCE, &option->mRcvBuffForce, sizeof(option->mRcvBuffForce));
        }

        if(option->mKeepAlive != -1) {
            sock->setSockOption(SOL_SOCKET, SO_KEEPALIVE, &option->mKeepAlive, sizeof(option->mKeepAlive));
        }

        if(option->mOobInline != -1) {
            sock->setSockOption(SOL_SOCKET, SO_OOBINLINE, &option->mOobInline, sizeof(option->mOobInline));
        }

        if(option->mNoCheck != -1) {
            sock->setSockOption(SOL_SOCKET, SO_NO_CHECK, &option->mNoCheck, sizeof(option->mNoCheck));
        }

        if(option->mPriority != -1) {
            sock->setSockOption(SOL_SOCKET, SO_PRIORITY, &option->mPriority, sizeof(option->mPriority));
        }

        if(option->mLingerOnOff != -1 && option->mLingerValue != -1) {
            struct linger ll;
            ll.l_onoff = option->mLingerOnOff;
            ll.l_linger = option->mLingerValue;
            
            sock->setSockOption(SOL_SOCKET, SO_LINGER, &ll, sizeof(struct linger));
        }

        if(option->mReUsePort != -1) {
            sock->setSockOption(SOL_SOCKET, SO_REUSEPORT, &option->mReUsePort, sizeof(option->mReUsePort));
        }

        if(option->mPassCred != -1) {
            sock->setSockOption(SOL_SOCKET, SO_PASSCRED, &option->mPassCred, sizeof(option->mPassCred));
        }

        if(option->mPeerCred != -1) {
            sock->setSockOption(SOL_SOCKET, SO_PEERCRED, &option->mPeerCred, sizeof(option->mPeerCred));
        }

        if(option->mRcvLoWat != -1) {
            sock->setSockOption(SOL_SOCKET, SO_RCVLOWAT, &option->mRcvLoWat, sizeof(option->mRcvLoWat));
        }

        if(option->mSndLoWat != -1) {
            sock->setSockOption(SOL_SOCKET, SO_SNDLOWAT, &option->mSndLoWat, sizeof(option->mSndLoWat));
        }

        if(option->mRcvTimeout != -1) {
            sock->setSockOption(SOL_SOCKET, SO_SNDLOWAT, &option->mRcvTimeout, sizeof(option->mRcvTimeout));
        }

        if(option->mSndLoWat != -1) {
            sock->setSockOption(SOL_SOCKET, SO_RCVTIMEO, &option->mSndLoWat, sizeof(option->mSndLoWat));
        }

        if(option->mSendTimeout != -1) {
            sock->setSockOption(SOL_SOCKET, SO_SNDTIMEO, &option->mSendTimeout, sizeof(option->mSendTimeout));
        }

        if(option->mBindToDevice != nullptr) {
            sock->setSockOption(SOL_SOCKET, SO_BINDTODEVICE, option->mBindToDevice, sizeof(struct ifreq));
        }

        if(option->mAttachFilter != nullptr) {
            sock->setSockOption(SOL_SOCKET, SO_ATTACH_FILTER, &option->mAttachFilter, sizeof(struct sock_fprog));
        }

        if(option->mDetachFilter != -1) {
            sock->setSockOption(SOL_SOCKET, SO_DETACH_FILTER, &option->mDetachFilter, sizeof(option->mDetachFilter));
        }

        if(option->mTimeStamp != -1) {
            sock->setSockOption(SOL_SOCKET, SO_TIMESTAMP, &option->mTimeStamp, sizeof(option->mTimeStamp));
        }

        if(option->mTimeStampNs != -1) {
            sock->setSockOption(SOL_SOCKET, SO_TIMESTAMPNS, &option->mTimeStampNs, sizeof(option->mTimeStampNs));
        }

        if(option->mTimeStampIng != -1) {
            sock->setSockOption(SOL_SOCKET, SO_TIMESTAMPING, &option->mTimeStampIng, sizeof(option->mTimeStampIng));
        }

        if(option->mBusyPoll != -1) {
            sock->setSockOption(SOL_SOCKET, SO_BUSY_POLL, &option->mBusyPoll, sizeof(option->mBusyPoll));
        }

        if(option->mMaxPacingRate != -1) {
            sock->setSockOption(SOL_SOCKET, SO_MAX_PACING_RATE, &option->mMaxPacingRate, sizeof(option->mMaxPacingRate));
        }
#ifdef SO_ATTACH_REUSEPORT_CBPF
        if(option->mReusePortCbpf != nullptr) {
            sock->setSockOption(SOL_SOCKET, SO_ATTACH_REUSEPORT_CBPF, option->mReusePortCbpf, sizeof(struct sock_fprog));
        }
#endif

#ifdef SO_ATTACH_REUSEPORT_EBPF
        if(option->mReusePortEbpf != -1) {
            sock->setSockOption(SOL_SOCKET, SO_ATTACH_REUSEPORT_EBPF, &option->mReusePortEbpf, sizeof(option->mReusePortEbpf));
        }
#endif

#ifdef SO_ZEROCOPY
        if(option->mZeroCopy != -1) {
            sock->setSockOption(SOL_SOCKET, SO_ZEROCOPY, &option->mZeroCopy, sizeof(option->mZeroCopy));
        }
#endif
    }
}

int _SocketImpl::close() {
    if(sock != nullptr) {
        sock->close();
        sock = nullptr;
    }
 
    return 0;
}

ByteArray _SocketImpl::receive() {
    ByteArray data = createByteArray(mBuffSize);
    int length = ::read(sock->getFd(),data->toValue(),1024);
    data->quickShrink(length);
    return data;
}

FileDescriptor _SocketImpl::getFileDescriptor() {
    return sock;
}

InetAddress _SocketImpl::getInetAddress() {
    return address;
}

void _SocketImpl::setInetAddress(InetAddress addr) {
    address = addr;
}

}
