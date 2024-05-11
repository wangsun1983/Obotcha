#ifndef __OBOTCHA_SOCKET_BUILDER_HPP__
#define __OBOTCHA_SOCKET_BUILDER_HPP__

#include "Object.hpp"
#include "Inet4Address.hpp"
#include "Socket.hpp"
#include "SocketOption.hpp"
#include "ServerSocket.hpp"
#include "FileDescriptor.hpp"
#include "AsyncOutputChannelPool.hpp"

namespace obotcha {

DECLARE_CLASS(SocketBuilder) {
public:
    _SocketBuilder() = default;
    
    _SocketBuilder* setAddress(InetAddress);
    _SocketBuilder* setOption(SocketOption);
    _SocketBuilder* setFileDescriptor(FileDescriptor);
    _SocketBuilder* setAsync(bool);
    _SocketBuilder* setAsyncPool(AsyncOutputChannelPool);
    
    Socket newSocket();
    Socket newDatagramSocket();
    Socket newSSLSocket();
    
    ServerSocket newServerSocket();
    ServerSocket newSSLServerSocket();
    
private:
    InetAddress mAddress = Inet4Address::New(st(InetAddress)::kDefaultPort);
    SocketOption mOption = nullptr;
    FileDescriptor mFd = nullptr;
    bool mIsAsync = false;
    AsyncOutputChannelPool mPool = nullptr;
};

}

#endif