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
#include "SocketImpl.hpp"
#include <atomic>

namespace obotcha {

class _SocketMonitor;

DECLARE_CLASS(Socket) {
public:
    friend class _SocketMonitor;
    friend class _SocketOutputStream;
    friend class _SocketInputStream;

    enum Type {
        Tcp,
        Udp,
        Local,
        Fd,
        SSL, //default SSL tcp
    };

    _Socket();
    _Socket(int,InetAddress addr,SocketOption option,String certificatePath = nullptr,String keyPath = nullptr);
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
    
    //for udp socket
    sp<_Socket> receiveFrom(ByteArray);

    void setType(int);

    static int DefaultBufferSize;
    
    void setSockImpl(SocketImpl);
    SocketImpl getSockImpl();
    
private:
    int type;

protected:
    SocketImpl mSock;
    Mutex mMutex;

    SocketOutputStream mOutputStream;
    SocketInputStream mInputStream;

};

}

#endif