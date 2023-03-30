#ifndef __OBOTCHA_SOCKET_INPUT_STREAM_HPP__
#define __OBOTCHA_SOCKET_INPUT_STREAM_HPP__

#include "Object.hpp"

#include "InputStream.hpp"
#include "SocketImpl.hpp"

namespace obotcha {

class _Socket;

DECLARE_CLASS(SocketInputStream) IMPLEMENTS(InputStream) {
public:
    _SocketInputStream(sp<_Socket>);
    _SocketInputStream(SocketImpl);

    long read(ByteArray buffer);

    long read(ByteArray buffer,int start);

    long read(ByteArray buffer,int start,int length);

    void close();

    bool isAsync();
    
    void setAsync(bool async); 

    //used for udp
    sp<_Socket> recvDatagram(ByteArray);

    ~_SocketInputStream();

private:
    SocketImpl mImpl;
};

}
#endif
