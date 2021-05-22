#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Socket.hpp"
#include "SocksSocketImpl.hpp"
#include "DatagramSocketImpl.hpp"
#include "LocalSocketImpl.hpp"
#include "InitializeException.hpp"
#include "SocketInputStream.hpp"
#include "SocketOutputStream.hpp"

namespace obotcha {

_Socket::_Socket(int v,InetAddress addr,SocketOption option) {
    mInput = nullptr;
    mOutput = nullptr;
    type = v;
    
    switch(v) {
        case Tcp:
            mSock = createSocksSocketImpl(addr,option);
        return;

        case Udp:
            mSock = createDatagramSocketImpl(addr,option);
        return;

        case Local:
            mSock = createLocalSocketImpl(addr,option);
        return;
    }

    Trigger(InitializeException,"ivalid type");
}

_Socket::_Socket(FileDescriptor descriptor) {
    mInput = nullptr;
    mOutput = nullptr;
    mSock = createSocketImpl(descriptor);
    type = Fd;
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

int _Socket::connect() {
    return mSock->connect();
}

int _Socket::bind() {
    return mSock->bind();
}

void _Socket::close() {
    mSock->close();

    if(mOutput != nullptr) {
        mOutput->close();
        mOutput = nullptr;
    }

    if(mInput != nullptr) {
        mInput->close();
        mOutput = nullptr;
    }
}

bool _Socket::isClosed() {
    FileDescriptor fd = mSock->getFileDescriptor();
    if(fd != nullptr) {
        return fd->isClosed();
    }

    return false;
}

InputStream _Socket::getInputStream() {
    if(mInput == nullptr) {
        mInput = createSocketInputStream(AutoClone(this));
    }
    return mInput;
}

OutputStream _Socket::getOutputStream() {
    if(mOutput == nullptr) {
        mOutput = createSocketOutputStream(AutoClone(this));
    }
    return mOutput;
}

FileDescriptor _Socket::getFileDescriptor() {
    return mSock->getFileDescriptor();
}

int _Socket::getType() {
    return type;
}

}
