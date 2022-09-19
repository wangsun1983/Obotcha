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
    protocol = UnKnown;
    mClosed = false;
}

_Socket::_Socket(int v, InetAddress addr, SocketOption option,String certificatePath,String keyPath):_Socket() {
    protocol = v;
    switch (v) {
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

    Trigger(InitializeException, "ivalid type");
}

_Socket::_Socket(FileDescriptor descriptor):_Socket() {
    mSock = createSocketImpl(descriptor);
    protocol = Fd;
}

void _Socket::setAsync(bool async) {
    mSock->getFileDescriptor()->setAsync(async);
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
    this->protocol = protocol;
}

int _Socket::connect() {
    return mSock->connect();
}

int _Socket::bind() {
    return mSock->bind();
}

void _Socket::close() {
    if(!mClosed) {
        mClosed = true;
        if(mInputStream != nullptr) {
            mInputStream->close();
        }

        if(mOutPutStream != nullptr) {
            mOutPutStream->close();
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
    if(mInputStream == nullptr) {
        mInputStream = createSocketInputStream(AutoClone(this));
    }
    return mInputStream;
}

OutputStream _Socket::getOutputStream() {
    if(mOutPutStream == nullptr) {
        mOutPutStream = createSocketOutputStream(AutoClone(this));
    }
    return mOutPutStream;
}

FileDescriptor _Socket::getFileDescriptor() {
    return mSock->getFileDescriptor();
}

int _Socket::getProtocol() {
    return protocol;
}

void _Socket::setSockImpl(SocketImpl impl) {
    this->mSock = impl;
}

SocketImpl _Socket::getSockImpl() {
    return mSock;
}

} // namespace obotcha
