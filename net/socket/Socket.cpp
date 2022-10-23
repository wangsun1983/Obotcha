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

int _Socket::DefaultBufferSize = 1024 * 4;

_Socket::_Socket() {
    mProtocol = UnKnown;
    mClosed = false;
    mSock = nullptr;
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
            mSock = createSocksSocketImpl(addr, option);
            return;

        case Udp:
            mSock = createDatagramSocketImpl(addr, option);
            return;

        case Local:
            mSock = createLocalSocketImpl(addr, option);
            return;

        case SSL:
            mSock = createSSLSocksSocketImpl(certificatePath,keyPath,addr,option);
            return;
    }

    Trigger(InitializeException, "invalid type");
}

_Socket::_Socket(FileDescriptor descriptor):_Socket() {
    mSock = createSocketImpl(descriptor);
    mOutputStream = createSocketOutputStream(mSock,mPool);
    mInputStream = createSocketInputStream(mSock);
    mProtocol = Fd;
}

void _Socket::setAsync(bool async,AsyncOutputChannelPool pool) {
    bool formerAsync = mIsAsync;
    if(formerAsync != async) {
        mSock->getFileDescriptor()->setAsync(async);
        //firstly,remove ouputstream from async pool£¡£¡£¡£¡;
        mOutputStream->setAsync(false);
        if(pool != nullptr) {
            mPool = pool;
        }
        mIsAsync = async;
        mOutputStream->setAsync(async,mPool);
        //mOutputStream = createSocketOutputStream(mSock,mPool);
        //mInputStream = createSocketInputStream(mSock);
    }
}

bool _Socket::isAsync() {
    return mSock->getFileDescriptor()->isAsync();
}

void _Socket::setInetAddress(InetAddress addr) {
    mSock->setInetAddress(addr);
}

InetAddress _Socket::getInetAddress() {
    return mSock->getInetAddress();
}

void _Socket::setProtocol(int protocol) {
    this->mProtocol = protocol;
}

int _Socket::connect() {
    if(mSock->connect() == 0) {
        mSock->getFileDescriptor()->setAsync(mIsAsync);
        setAsync(mIsAsync,mPool);
        //mOutputStream = createSocketOutputStream(mSock,mPool);
        //mInputStream = createSocketInputStream(mSock);
        return 0;
    }
    return -1;
}

int _Socket::bind() {
    int ret = mSock->bind();
    mOutputStream = createSocketOutputStream(mSock,mPool);
    mInputStream = createSocketInputStream(mSock);

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

        if (mSock != nullptr) {
            mSock->close();
        }
    }
}

bool _Socket::isClosed() {
    return mClosed;
}

sp<_Socket> _Socket::receiveFrom(ByteArray buff) {
    return mSock->receiveFrom(buff);
}

InputStream _Socket::getInputStream() {
    //if(mInputStream == nullptr) {
    //    mInputStream = createSocketInputStream(AutoClone(this));
    //}
    return mInputStream;
}

OutputStream _Socket::getOutputStream() {
    //if(mOutputStream == nullptr) {
    //    mOutputStream = createSocketOutputStream(AutoClone(this));
    //}
    return mOutputStream;
}

FileDescriptor _Socket::getFileDescriptor() {
    return mSock->getFileDescriptor();
}

int _Socket::getProtocol() {
    return mProtocol;
}

void _Socket::setSockImpl(SocketImpl impl) {
    this->mSock = impl;
}

SocketImpl _Socket::getSockImpl() {
    return mSock;
}

} // namespace obotcha
