#ifndef __OBOTCHA_SOCKET_OUTPUT_STREAM_HPP__
#define __OBOTCHA_SOCKET_OUTPUT_STREAM_HPP__


#include "Object.hpp"
#include "StrongPointer.hpp"

#include "OutputStream.hpp"
#include "AsyncOutputChannel.hpp"
#include "FileDescriptor.hpp"

namespace obotcha {

class _Socket;

DECLARE_SIMPLE_CLASS(SocketOutputStream) IMPLEMENTS(OutputStream) {
public:
    _SocketOutputStream(sp<_Socket>);

    long write(char c);
    
    long write(ByteArray buff,long size = 0);

    void close();

    void flush();

private:
    long _write(FileDescriptor,ByteArray);

    sp<_Socket> mSocket;

    AsyncOutputChannel mChannel;

    struct sockaddr_in server_addr;
};

}

#endif
