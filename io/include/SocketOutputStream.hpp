#ifndef __OBOTCHA_SOCKET_OUTPUT_STREAM_HPP__
#define __OBOTCHA_SOCKET_OUTPUT_STREAM_HPP__

#include "Object.hpp"

#include "AsyncOutputChannel.hpp"
#include "AsyncOutputChannelPool.hpp"
#include "FileDescriptor.hpp"
#include "OutputStream.hpp"
#include "SocketImpl.hpp"

namespace obotcha {

class _Socket;

DECLARE_CLASS(SocketOutputStream) IMPLEMENTS(OutputStream) {
  public:
    _SocketOutputStream(sp<_Socket>,AsyncOutputChannelPool pool = nullptr);
    _SocketOutputStream(SocketImpl,AsyncOutputChannelPool pool = nullptr);

    long write(char c);

    long write(ByteArray buff);

    long write(ByteArray, int start);

    long write(ByteArray, int start, int len);

    void setAsync(bool,AsyncOutputChannelPool pool = nullptr);
    
    void close();

    void flush();
    
    SocketImpl getSocket();
    
    ~_SocketOutputStream();

  private:
    long _write(ByteArray,int offset);

    //sp<_Socket> mSocket;
    FileDescriptor mFileDescriptor;
    SocketImpl mImpl;

    //Mutex mChannelMutex;
    AsyncOutputChannel mChannel;
    AsyncOutputChannelPool mPool;

    static AsyncOutputChannelPool defaultOutputChannelPool;

    //struct sockaddr_in server_addr;
    //struct sockaddr_in6 server_addr_v6;
};

} // namespace obotcha

#endif
