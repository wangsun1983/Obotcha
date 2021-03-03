#ifndef __OBOTCHA_SOCKET_IMPL_HPP__
#define __OBOTCHA_SOCKET_IMPL_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "InetAddress.hpp"
#include "InputStream.hpp"
#include "OutputStream.hpp"
#include "SocketOption.hpp"
#include "Error.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(SocketImpl) {
public:
    _SocketImpl(){}
    _SocketImpl(int);
    _SocketImpl(InetAddress,SocketOption);
    virtual int connect() {return -NotSupport;};
    virtual int bind() {return -NotSupport;};
    virtual int accept() {return -NotSupport;}; //TOOD
    
    int close();
    int getFd();

    InetAddress getInetAddress();
    void setInetAddress(InetAddress);
    
protected:
    int sock;
    InetAddress address;
    SocketOption option;
    struct sockaddr_in mSockAddr;
};

}

#endif