#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Socket.hpp"
#include "SocksSocketImpl.hpp"
#include "DatagramSocketImpl.hpp"
#include "InitializeException.hpp"
#include "SocketInputStream.hpp"
#include "SocketOutputStream.hpp"

namespace obotcha {

_Socket::_Socket(int v,InetAddress addr,SocketOption option) {
    mInput = nullptr;
    mOutput = nullptr;
    mStatus = Idle;

    switch(v) {
        case Tcp:
        mSock = createSocksSocketImpl(addr,option);
        return;

        case Udp:
        mSock = createDatagramSocketImpl(addr,option);
        return;
    }

    Trigger(InitializeException,"ivalid type");
}

_Socket::_Socket(int fd) {
    mInput = nullptr;
    mOutput = nullptr;
    mSock = createSocketImpl(fd);
    mStatus = Idle;
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