#ifndef __OBOTCHA_SOCKET_INPUT_STREAM_HPP__
#define __OBOTCHA_SOCKET_INPUT_STREAM_HPP__

#include "Object.hpp"

#include "InputStream.hpp"
#include "SocketImpl.hpp"

namespace obotcha {

class _Socket;

DECLARE_CLASS(SocketInputStream) IMPLEMENTS(InputStream) {
public:
    explicit _SocketInputStream(sp<_Socket>);
    explicit _SocketInputStream(SocketImpl);
    long read(ByteArray buffer) override;
    long read(ByteArray buffer,int start) override;
    long read(ByteArray buffer,int start,int length) override;
    void close() override;
    bool isAsync();
    void setAsync(bool async);

    //used for udp
    sp<_Socket> recvDatagram(ByteArray);
    ~_SocketInputStream() override;

private:
    SocketImpl mImpl;
};

}
#endif
