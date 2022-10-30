#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "DatagramSocketImpl.hpp"
#include "InitializeException.hpp"
#include "LocalSocketImpl.hpp"
#include "Socket.hpp"
#include "SocketInputStream.hpp"
#include "SocketOutputStream.hpp"
#include "SocksSocketImpl.hpp"
#include "SSLSocksSocketImpl.hpp"
#include "System.hpp"

namespace obotcha {

_Socket::_Socket() {
    mProtocol = UnKnown;
    mClosed = false;
    mSockImpl = nullptr;
    mIsAsync = false;
    mPool = nullptr;
}

_Socket::_Socket(int protocol, 
                 InetAddress addr, 
                 SocketOption option,
                 String certificatePath,
                 String keyPath,
                 bool isAsync,
                 AsyncOutputChannelPool pool):_Socket() {
    mProtocol = protocol;
    mPool = pool;
    mIsAsync = isAsync;

    switch (protocol) {
        case Tcp:
            mSockImpl = createSocksSocketImpl(addr, option);
            return;

        case Udp:
            mSockImpl = createDatagramSocketImpl(addr, option);
            return;

        case Local:
            mSockImpl = createLocalSocketImpl(addr, option);
            return;

        case SSL:
            mSockImpl = createSSLSocksSocketImpl(certificatePath,keyPath,addr,option);
            return;
    }

    Trigger(InitializeException, "invalid type");
}

_Socket::_Socket(FileDescriptor descriptor):_Socket() {
    mSockImpl = createSocketImpl(descriptor);
    mOutputStream = createSocketOutputStream(mSockImpl,mPool);
    mInputStream = createSocketInputStream(mSockImpl);
    mProtocol = Fd;
}
_Socket::_Socket(int protocol,SocketImpl impl):_Socket() {
    mSockImpl = impl;
    mProtocol = protocol;
}

void _Socket::setAsync(bool async,AsyncOutputChannelPool pool) {
    bool formerAsync = mIsAsync;
    if(formerAsync != async) {
        mSockImpl->getFileDescriptor()->setAsync(async);
        //firstly,remove ouputstream from async pool！！！！;
        mOutputStream->setAsync(false);
        if(pool != nullptr) {
            mPool = pool;
        }
        mIsAsync = async;
        mOutputStream->setAsync(async,mPool);
    }
}

bool _Socket::isAsync() {
    return mSockImpl->getFileDescriptor()->isAsync();
}

InetAddress _Socket::getInetAddress() {
    return mSockImpl->getInetAddress();
}

int _Socket::connect() {
    if(mSockImpl->connect() == 0) {
        mSockImpl->getFileDescriptor()->setAsync(mIsAsync);
        setAsync(mIsAsync,mPool);
        return 0;
    }
    return -1;
}

int _Socket::bind() {
    int ret = mSockImpl->bind();
    mOutputStream = createSocketOutputStream(mSockImpl,mPool);
    mInputStream = createSocketInputStream(mSockImpl);

    return ret;
}

void _Socket::close() {
    if(!mClosed) {
        mClosed = true;
        if(mInputStream != nullptr) {
            mInputStream->close();
        }

        if(mOutputStream != nullptr) {
            mOutputStream->close();
        }

        if (mSockImpl != nullptr) {
            mSockImpl->close();
        }
    }
}

bool _Socket::isClosed() {
    return mClosed;
}

sp<_Socket> _Socket::recvDatagram(ByteArray buff) {
    return mSockImpl->recvDatagram(buff);
}

InputStream _Socket::getInputStream() {
    return mInputStream;
}

OutputStream _Socket::getOutputStream() {
    return mOutputStream;
}

FileDescriptor _Socket::getFileDescriptor() {
    return mSockImpl->getFileDescriptor();
}

int _Socket::getProtocol() {
    return mProtocol;
}

} // namespace obotcha
