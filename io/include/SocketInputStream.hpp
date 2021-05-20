#ifndef __OBOTCHA_SOCKET_INPUT_STREAM_HPP__
#define __OBOTCHA_SOCKET_INPUT_STREAM_HPP__


#include "Object.hpp"
#include "StrongPointer.hpp"

#include "InputStream.hpp"

namespace obotcha {

class _Socket;

DECLARE_SIMPLE_CLASS(SocketInputStream) IMPLEMENTS(InputStream) {
public:

    _SocketInputStream(sp<_Socket>);

    long read(ByteArray buffer);

    void close();

    ~_SocketInputStream();

    bool isAsync();
    
    void setAsync(bool async); 

private:
    sp<_Socket> mSocket;
};

}
#endif
