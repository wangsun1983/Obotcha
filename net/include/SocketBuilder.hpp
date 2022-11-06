#ifndef __OBOTCHA_SOCKET_BUILDER_HPP__
#define __OBOTCHA_SOCKET_BUILDER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ByteArray.hpp"
#include "Socket.hpp"
#include "SocketOption.hpp"
#include "ServerSocket.hpp"
#include "FileDescriptor.hpp"
#include "AsyncOutputChannelPool.hpp"

namespace obotcha {

DECLARE_CLASS(SocketBuilder) {
public:
    _SocketBuilder();
    
    _SocketBuilder* setAddress(InetAddress);
    _SocketBuilder* setOption(SocketOption);
    _SocketBuilder* setFileDescriptor(FileDescriptor);
    _SocketBuilder* setSSLCretificatePath(String);
    _SocketBuilder* setSSLKeyPath(String);
    _SocketBuilder* setAsync(bool);
    _SocketBuilder* setAsyncPool(AsyncOutputChannelPool);
    
    Socket newSocket();
    Socket newDatagramSocket();
    Socket newSSLSocket();
    
    ServerSocket newServerSocket();
    ServerSocket newSSLServerSocket();
    
private:
    InetAddress address;
    SocketOption option;
    FileDescriptor fd;
    String mCertificatePath;
    String mKeyPath;
    bool mIsAsync;
    AsyncOutputChannelPool mPool;
};

}

#endif