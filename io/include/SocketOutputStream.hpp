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
    long write(char c) override;
    long write(ByteArray buff) override;
    long write(ByteArray, uint64_t start) override;
    long write(ByteArray, uint64_t start, uint64_t len) override;
    void setAsync(bool,AsyncOutputChannelPool pool = nullptr) override;
    void close() override;
    void flush() override;
    SocketImpl getSocket();
    ~_SocketOutputStream() override = default;

  private:
    long _write(ByteArray,uint64_t offset);

    FileDescriptor mFileDescriptor;
    SocketImpl mImpl;

    AsyncOutputChannel mChannel;
    AsyncOutputChannelPool mPool;
    static AsyncOutputChannelPool defaultOutputChannelPool;

};

} // namespace obotcha

#endif
