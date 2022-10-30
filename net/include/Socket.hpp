#ifndef __OBOTCHA_SOCKET_HPP__
#define __OBOTCHA_SOCKET_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ByteArray.hpp"
#include "SocketImpl.hpp"
#include "SocketOption.hpp"
#include "SocketInputStream.hpp"
#include "SocketOutputStream.hpp"
#include "FileDescriptor.hpp"
#include "SocketImpl.hpp"
#include "AsyncOutputChannelPool.hpp"
#include <atomic>

namespace obotcha {

class _SocketMonitor;
class _SSLServerSocketImpl;

DECLARE_CLASS(Socket) {
public:
    friend class _SocketMonitor;
    friend class _SocketOutputStream;
    friend class _SocketInputStream;

    friend class _SSLServerSocketImpl;

    enum Protocol {
        UnKnown = 0,
        Tcp,
        Udp,
        Local,
        Fd,
        SSL, //default SSL tcp
    };

    _Socket();

    _Socket(int protocol,
            InetAddress addr,
            SocketOption option,
            String certificatePath = nullptr,
            String keyPath = nullptr,
            bool isAsync = false,
            AsyncOutputChannelPool pool = nullptr);

    _Socket(FileDescriptor);

    _Socket(int protocol,SocketImpl impl);

    void setAsync(bool,AsyncOutputChannelPool pool = nullptr);

    bool isAsync();
    
    int connect();
    
    int bind();

    void close();

    bool isClosed();

    FileDescriptor getFileDescriptor();
    
    InetAddress getInetAddress();

    InputStream getInputStream();

    OutputStream getOutputStream();
    
    //for udp socket
    sp<_Socket> recvDatagram(ByteArray);
    
    int getProtocol();
    
private:
    int mProtocol;
    
    OutputStream mOutputStream;
    
    InputStream mInputStream;

    AsyncOutputChannelPool mPool;
    
    bool mIsAsync;

protected:
    SocketImpl mSockImpl;
    
    bool mClosed;
};

}

#endif