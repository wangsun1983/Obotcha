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
DECLARE_CLASS(SocketImpl) {
public:
    _SocketImpl(){};
    _SocketImpl(FileDescriptor);
    _SocketImpl(InetAddress,SocketOption);
    virtual int connect() {Trigger(MethodNotSupportException,"not support");}
    virtual int bind() {Trigger(MethodNotSupportException,"not support");}
    virtual sp<_Socket> accept() {Trigger(MethodNotSupportException,"not support");}//TOOD
    
    virtual sp<_Socket> receiveFrom(ByteArray){Trigger(MethodNotSupportException,"not support");}

    //move all read write function to socket
    //default is tcp's read & write function
    virtual int write(ByteArray,int start = 0,int length = -1);
    virtual int read(ByteArray,int start = 0,int length = -1);
    virtual ByteArray read();

    int close();
    FileDescriptor getFileDescriptor();

    void setRecvBuff(int);
    
    InetAddress getInetAddress();
    void setInetAddress(InetAddress);
    
protected:
    void setOptions();
    FileDescriptor sock;
    InetAddress address;
    SocketOption option;
    
    struct sockaddr_in mSockAddr; //ipv4
    struct sockaddr_in6 mSockAddrV6; //ipv6

    int mBuffSize;

private:
    void _init();
};

}

#endif