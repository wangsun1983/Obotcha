#ifndef __OBOTCHA_SOCKET_IMPL_HPP__
#define __OBOTCHA_SOCKET_IMPL_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "InetAddress.hpp"
#include "InputStream.hpp"
#include "OutputStream.hpp"
#include "SocketOption.hpp"
#include "Error.hpp"
#include "MethodNotSupportException.hpp"
namespace obotcha {

class _Socket;
DECLARE_SIMPLE_CLASS(SocketImpl) {
public:
    _SocketImpl(){}
    _SocketImpl(int);
    _SocketImpl(InetAddress,SocketOption);
    virtual int connect() {Trigger(MethodNotSupportException,"not support");};
    virtual int bind() {Trigger(MethodNotSupportException,"not support");};
    virtual sp<_Socket> accept() {Trigger(MethodNotSupportException,"not support");}; //TOOD
    
    int close();
    int getFd();

    ByteArray receive();

    InetAddress getInetAddress();
    void setInetAddress(InetAddress);
    
protected:
    void setOptions();
    int sock;
    InetAddress address;
    SocketOption option;
    struct sockaddr_in mSockAddr;
    byte *mBuff;
    int mBuffSize;
};

}

#endif