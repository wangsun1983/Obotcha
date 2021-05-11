#include "SocketImpl.hpp"

namespace obotcha {

_SocketImpl::_SocketImpl(int fd) {
    sock = fd;
    mBuffSize = -1;
    mBuff = nullptr;
}

_SocketImpl::_SocketImpl(InetAddress address,SocketOption option) {
    this->address = address;
    this->option = option;
    this->mBuff = nullptr;
    this->mBuffSize = -1;

/*
    if(option != nullptr && option->getBuffSize() >= 0 ) {
        mBuffSize = option->getBuffSize();
        mBuff = new byte[mBuffSize];
    }
*/
}

void _SocketImpl::setOptions() {
    if(option != nullptr) {
        if(option->mReUseAddr != -1) {
            setsockopt(this->sock, SOL_SOCKET, SO_REUSEADDR, &option->mReUseAddr, sizeof(option->mReUseAddr));
        }

        if(option->mDontRoute != -1) {
            setsockopt(this->sock, SOL_SOCKET, SO_DONTROUTE, &option->mDontRoute, sizeof(option->mDontRoute));
        }

        if(option->mBroadCast != -1) {
            setsockopt(this->sock, SOL_SOCKET, SO_BROADCAST, &option->mBroadCast, sizeof(option->mBroadCast));
        }

        if(option->mSendBuf != -1) {
            setsockopt(this->sock, SOL_SOCKET, SO_SNDBUF, &option->mSendBuf, sizeof(option->mSendBuf));
        }

        if(option->mRcvBuff != -1) {
            setsockopt(this->sock, SOL_SOCKET, SO_RCVBUF, &option->mRcvBuff, sizeof(option->mRcvBuff));
        }

        if(option->mSendBuffForce != -1) {
            setsockopt(this->sock, SOL_SOCKET, SO_SNDBUFFORCE, &option->mSendBuffForce, sizeof(option->mSendBuffForce));
        }

        if(option->mRcvBuffForce != -1) {
            setsockopt(this->sock, SOL_SOCKET, SO_RCVBUFFORCE, &option->mRcvBuffForce, sizeof(option->mRcvBuffForce));
        }

        if(option->mKeepAlive != -1) {
            setsockopt(this->sock, SOL_SOCKET, SO_KEEPALIVE, &option->mKeepAlive, sizeof(option->mKeepAlive));
        }

        if(option->mOobInline != -1) {
            setsockopt(this->sock, SOL_SOCKET, SO_OOBINLINE, &option->mOobInline, sizeof(option->mOobInline));
        }

        if(option->mNoCheck != -1) {
            setsockopt(this->sock, SOL_SOCKET, SO_NO_CHECK, &option->mNoCheck, sizeof(option->mNoCheck));
        }

        if(option->mPriority != -1) {
            setsockopt(this->sock, SOL_SOCKET, SO_PRIORITY, &option->mPriority, sizeof(option->mPriority));
        }

        if(option->mLingerOnOff != -1 && option->mLingerValue != -1) {
            //TODO
            //setsockopt(this->sock, SOL_SOCKET, SO_KEEPALIVE, &option->mKeepAlive, sizeof(option->mKeepAlive));
        }

        if(option->mReUsePort != -1) {
            setsockopt(this->sock, SOL_SOCKET, SO_REUSEPORT, &option->mReUsePort, sizeof(option->mReUsePort));
        }

        if(option->mPassCred != -1) {
            setsockopt(this->sock, SOL_SOCKET, SO_PASSCRED, &option->mPassCred, sizeof(option->mPassCred));
        }

        if(option->mPeerCred != -1) {
            setsockopt(this->sock, SOL_SOCKET, SO_PEERCRED, &option->mPeerCred, sizeof(option->mPeerCred));
        }

        if(option->mRcvLoWat != -1) {
            setsockopt(this->sock, SOL_SOCKET, SO_RCVLOWAT, &option->mRcvLoWat, sizeof(option->mRcvLoWat));
        }

        if(option->mPassCred != -1) {
            setsockopt(this->sock, SOL_SOCKET, SO_PASSCRED, &option->mPassCred, sizeof(option->mPassCred));
        }
    }
}

int _SocketImpl::close() {
    if(sock != -1) {
        ::close(sock);
        sock = -1;
    }

    if(mBuff != nullptr) {
        delete []mBuff;
    }
    
    return 0;
}

ByteArray _SocketImpl::receive() {
    if(mBuffSize > 0) {
        int length = ::read(sock,mBuff,mBuffSize);
        return createByteArray(mBuff,length);
    }

    byte buff[1024];
    int length = ::read(sock,buff,1024);
    return createByteArray(buff,length);
}

int _SocketImpl::getFd() {
    return this->sock;
}

InetAddress _SocketImpl::getInetAddress() {
    return address;
}

void _SocketImpl::setInetAddress(InetAddress addr) {
    address = addr;
}

}
