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

    _Socket();

    _Socket(int protocol,
            InetAddress addr,
            SocketOption option,
            bool isAsync = false,
            AsyncOutputChannelPool pool = nullptr);

    _Socket(SocketImpl impl,AsyncOutputChannelPool pool = nullptr);

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

    int getProtocol();
    
private:
    int mProtocol;
    
    OutputStream mOutputStream;
    
    InputStream mInputStream;

    AsyncOutputChannelPool mPool;
    
    bool mIsAsync;

    void updateStream();

protected:
    SocketImpl mSockImpl;
    
    bool mClosed;
};

}

#endif