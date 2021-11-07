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

namespace obotcha {

int _Socket::DefaultBufferSize = 1024 * 4;

_Socket::_Socket(int v, InetAddress addr, SocketOption option) {
    mInput = nullptr;
    mOutput = nullptr;
    type = v;
    mMutex = createMutex();

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
    }
    Trigger(InitializeException, "ivalid type");
}

_Socket::_Socket(FileDescriptor descriptor) {
    mInput = nullptr;
    mOutput = nullptr;
    mSock = createSocketImpl(descriptor);
    type = Fd;
    mMutex = createMutex();
}

void _Socket::setAsync(bool async) {
    mSock->getFileDescriptor()->setAsync(async);
    mOutput = nullptr;
    mInput = nullptr;
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

void _Socket::setType(int type) { 
    this->type = type; 
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

    if (mOutput != nullptr) {
        mOutput->close();
        mOutput = nullptr;
    }

    if (mInput != nullptr) {
        mInput->close();
        mInput = nullptr;
    }
}

bool _Socket::isClosed() {
    AutoLock l(mMutex);
    return mSock == nullptr;
}

InputStream _Socket::getInputStream() {
    if (mInput == nullptr) {
        mInput = createSocketInputStream(AutoClone(this));
    }
    return mInput;
}

OutputStream _Socket::getOutputStream() {
    if (mOutput == nullptr) {
        mOutput = createSocketOutputStream(AutoClone(this));
    }
    return mOutput;
}

FileDescriptor _Socket::getFileDescriptor() {
    return mSock->getFileDescriptor();
}

int _Socket::getType() { return type; }

} // namespace obotcha
