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
#include "FileDescriptor.hpp"

namespace obotcha {

class _Socket;
DECLARE_SIMPLE_CLASS(SocketImpl) {
public:
    _SocketImpl(){}
    _SocketImpl(FileDescriptor);
    _SocketImpl(InetAddress,SocketOption);
    virtual int connect() {Trigger(MethodNotSupportException,"not support");};
    virtual int bind() {Trigger(MethodNotSupportException,"not support");};
    virtual sp<_Socket> accept() {Trigger(MethodNotSupportException,"not support");}; //TOOD
    
    int close();
    FileDescriptor getFileDescriptor();

    void setRecvBuff(int);
    ByteArray receive();

    InetAddress getInetAddress();
    void setInetAddress(InetAddress);
    
protected:
    void setOptions();
    FileDescriptor sock;
    InetAddress address;
    SocketOption option;
    struct sockaddr_in mSockAddr;
    int mBuffSize;

private:
    void _init();
};

}

#endif