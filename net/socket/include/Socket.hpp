#ifndef __OBOTCHA_SOCKET_HPP__
#define __OBOTCHA_SOCKET_HPP__

#include "Object.hpp"
#include "SocketImpl.hpp"
#include "SocketOption.hpp"
#include "SocketInputStream.hpp"
#include "SocketOutputStream.hpp"
#include "FileDescriptor.hpp"
#include "SocketImpl.hpp"
#include "AsyncOutputChannelPool.hpp"
#include "NetProtocol.hpp"

namespace obotcha {

class _SocketMonitor;
class _SSLServerSocketImpl;

DECLARE_CLASS(Socket) IMPLEMENTS(NetProtocol) {
public:
    friend class _SocketMonitor;
    friend class _SocketOutputStream;
    friend class _SocketInputStream;
    friend class _SSLServerSocketImpl;

    _Socket() = default;

    _Socket(int protocol,
            InetAddress addr,
            SocketOption option,
            bool isAsync = false,
            AsyncOutputChannelPool pool = nullptr);

    _Socket(SocketImpl impl,
            InetAddress addr = nullptr,
            AsyncOutputChannelPool pool = nullptr);

    void setAsync(bool,AsyncOutputChannelPool pool = nullptr);

    bool isAsync() const;
    
    int connect();
    
    int bind();

    void close();

    bool isClosed() const;

    FileDescriptor getFileDescriptor();
    
    InetAddress getInetAddress();

    InputStream getInputStream();

    OutputStream getOutputStream();

    int getProtocol() const;
    
private:
    int mProtocol = UnKnown;
    
    OutputStream mOutputStream;
    
    InputStream mInputStream;

    AsyncOutputChannelPool mPool = nullptr;
    
    bool mIsAsync = false;

    void updateStream();

protected:
    SocketImpl mSockImpl = nullptr;
    
    bool mClosed = false;
};

}

#endif