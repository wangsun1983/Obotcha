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

_Socket::_Socket(int fd) {
    mInput = nullptr;
    mOutput = nullptr;
    mSock = createSocketImpl(fd);
    mStatus = Idle;
    type = Fd;
}

void _Socket::setAsync() {
    if(mStatus != Closed) {
        fcntl(mSock->getFd(), F_SETFL, fcntl(mSock->getFd(), F_GETFL, 0)| O_NONBLOCK);
    }
}

bool _Socket::isAsync() {
    if(mStatus != Closed) {
        return (fcntl(mSock->getFd(),F_GETFL) & O_NONBLOCK) != 0;
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
    }

    if(mInput != nullptr) {
        mInput->close();
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

int _Socket::getFd() {
    return mSock->getFd();
}

int _Socket::getType() {
    return type;
}

}
