#ifndef __OBOTCHA_SOCKET_OUTPUT_STREAM_HPP__
#define __OBOTCHA_SOCKET_OUTPUT_STREAM_HPP__


#include "Object.hpp"
#include "StrongPointer.hpp"

#include "OutputStream.hpp"

namespace obotcha {

class _Socket;

DECLARE_SIMPLE_CLASS(SocketOutputStream) IMPLEMENTS(OutputStream) {
public:
    _SocketOutputStream(sp<_Socket>);

    long write(char c);
    
    long write(ByteArray);

    long write(ByteArray buff,long size);

    void close();

    void flush();

private:
    sp<_Socket> mSocket;
};

}
#endif
