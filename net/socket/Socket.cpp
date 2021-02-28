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

_Socket::_Socket(int v,InetAddress addr, int port,SocketOption option) {
    switch(v) {
        case Tcp:
        mSock = createSocksSocketImpl(addr,port,option);
        return;

        case Udp:
        mSock = createDatagramSocketImpl(addr,port,option);
        return;
    }

    Trigger(InitializeException,"ivalid type");
}

int _Socket::connect() {
    return mSock->connect();
}

void _Socket::close() {
    //TODO
}

InputStream _Socket::getInputStream() {
    return createSocketInputStream(AutoClone(this));
}

OutputStream _Socket::getOutputStream() {
    return createSocketOutputStream(AutoClone(this));
}

int _Socket::getFd() {
    return mSock->getFd();
}

int _Socket::getType() {
    return type;
}

}
