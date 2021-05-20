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
    mStatus = Idle;
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
    mStatus = Idle;
    type = Fd;
}

void _Socket::setAsync(bool async) {
    if(mOutput != nullptr) {
        mOutput->setAsync(async);
    }

    if(mInput != nullptr) {
        mInput->setAsync(async);
    }
}

bool _Socket::isAsync() {
    if(mStatus != Closed) {
        return mOutput->isAsync();
    }

    return false;
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

    mStatus = Closed;
}

bool _Socket::isClosed() {
    return mStatus == Closed;
}

InputStream _Socket::getInputStream() {
    if(isClosed()) {
        return nullptr;
    }

    if(mInput == nullptr) {
        mInput = createSocketInputStream(AutoClone(this));
    }
    return mInput;
}

OutputStream _Socket::getOutputStream() {
    if(isClosed()) {
        return nullptr;
    }
    
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
