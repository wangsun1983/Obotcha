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
    mMutex = createMutex();
    mOutputStream = nullptr;
    mInputStream = nullptr;
    protocol = UnKnown;
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
    AutoLock l(mMutex);
    if (mSock != nullptr) {
        mSock->close();
        mSock = nullptr;
    }

    if(mOutputStream != nullptr) {
        mOutputStream->close();
        mOutputStream = nullptr;
    }

    if(mInputStream != nullptr) {
        mInputStream->close();
        mInputStream = nullptr;
    }
}

bool _Socket::isClosed() {
    AutoLock l(mMutex);
    return mSock == nullptr;
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
    if(mOutputStream == nullptr) {
        mOutputStream = createSocketOutputStream(AutoClone(this));
    }
    return mOutputStream;
}

FileDescriptor _Socket::getFileDescriptor() {
    return (mSock == nullptr)?nullptr:mSock->getFileDescriptor();
}

int _Socket::getProtocol() { 
    return protocol; 
}

void _Socket::setSockImpl(SocketImpl impl) {
    AutoLock l(mMutex);
    this->mSock = impl;
}

SocketImpl _Socket::getSockImpl() {
    AutoLock l(mMutex);
    return mSock;
}

} // namespace obotcha
