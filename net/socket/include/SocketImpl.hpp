#ifndef __OBOTCHA_SOCKET_IMPL_HPP__
#define __OBOTCHA_SOCKET_IMPL_HPP__

#include "Object.hpp"
#include "InetAddress.hpp"
#include "SocketOption.hpp"
#include "MethodNotSupportException.hpp"
#include "FileDescriptor.hpp"
#include "OutputWriter.hpp"

namespace obotcha {

class _Socket;
DECLARE_CLASS(SocketImpl) IMPLEMENTS(OutputWriter){
public:
    _SocketImpl();
    explicit _SocketImpl(FileDescriptor);
    _SocketImpl(InetAddress,SocketOption);
    virtual int connect() {Trigger(MethodNotSupportException,"not support");}
    virtual int bind() {Trigger(MethodNotSupportException,"not support");}
    virtual sp<_Socket> accept() {Trigger(MethodNotSupportException,"not support");}//TOOD
    virtual sp<_Socket> recvDatagram(ByteArray){Trigger(MethodNotSupportException,"not support");}
    
    //move all read write function to socket
    //default is tcp's read & write function
    virtual int write(ByteArray,int start = 0,int length = 0);
    virtual int read(ByteArray,int start = 0,int length = 0);
    virtual ByteArray read();

    virtual int close();
    virtual FileDescriptor getFileDescriptor();

    InetAddress getInetAddress();
    void setInetAddress(InetAddress);
    
protected:
    FileDescriptor mSock;  
    InetAddress mAddress;
    SocketOption mOption;
    int mBuffSize;

    int computeSutiableSize(ByteArray,int start,int length);

private:
    void init();
};

}

#endif