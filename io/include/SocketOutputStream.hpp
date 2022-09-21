#ifndef __OBOTCHA_SOCKET_OUTPUT_STREAM_HPP__
#define __OBOTCHA_SOCKET_OUTPUT_STREAM_HPP__

#include <arpa/inet.h>
#include <functional>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "AsyncOutputChannel.hpp"
#include "FileDescriptor.hpp"
#include "OutputStream.hpp"
#include "SocketImpl.hpp"
#include "Mutex.hpp"
#include "AutoLock.hpp"

namespace obotcha {

class _Socket;

DECLARE_CLASS(SocketOutputStream) IMPLEMENTS(OutputStream,AsyncOutputWriter) {
  public:
    _SocketOutputStream(sp<_Socket>);
    _SocketOutputStream(SocketImpl);

    long write(char c);

    long write(ByteArray buff);

    long write(ByteArray, int start);

    long write(ByteArray, int start, int len);

    void close();

    void flush();
    
    long asyncWrite(ByteArray,int);

    ~_SocketOutputStream();

  private:
    long _write(ByteArray,int offset);

    //sp<_Socket> mSocket;
    FileDescriptor fileDescriptor;
    SocketImpl impl;

    //Mutex mChannelMutex;
    AsyncOutputChannel mChannel;

    struct sockaddr_in server_addr;
    struct sockaddr_in6 server_addr_v6;
};

} // namespace obotcha

#endif
