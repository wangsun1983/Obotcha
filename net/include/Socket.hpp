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
#include <atomic>

namespace obotcha {

DECLARE_SIMPLE_CLASS(Socket) {
public:
    enum Type {
        Tcp,
        Udp,
        Local,
        Fd,
    };

    _Socket(int,InetAddress host,SocketOption option);
    _Socket(FileDescriptor);
    void setAsync(bool);
    bool isAsync();
    
    int connect();
    int bind();

    void close();
    bool isClosed();

    FileDescriptor getFileDescriptor();
    int getType();

    void setInetAddress(InetAddress);
    InetAddress getInetAddress();

    InputStream getInputStream();
    OutputStream getOutputStream();

    void setType(int);

    static int DefaultBufferSize;
    
private:
    int type;

protected:
    SocketImpl mSock; 
    SocketInputStream mInput;
    SocketOutputStream mOutput;

};

}

#endif