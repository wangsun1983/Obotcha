#ifndef __OBOTCHA_SOCKET_INPUT_STREAM_HPP__
#define __OBOTCHA_SOCKET_INPUT_STREAM_HPP__


#include "Object.hpp"
#include "StrongPointer.hpp"

#include "InputStream.hpp"
#include "SocketImpl.hpp"

namespace obotcha {

class _Socket;

DECLARE_CLASS(SocketInputStream) IMPLEMENTS(InputStream) {
public:

    _SocketInputStream(sp<_Socket>);

    long read(ByteArray buffer);

    long read(ByteArray buffer,int start);

    long read(ByteArray buffer,int start,int length);

    void close();

    ~_SocketInputStream();

    bool isAsync();
    
    void setAsync(bool async); 

private:
    //sp<_Socket> mSocket;
    SocketImpl impl;
};

}
#endif
