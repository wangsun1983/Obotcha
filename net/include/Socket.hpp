#ifndef __OBOTCHA_SOCKET_HPP__
#define __OBOTCHA_SOCKET_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ByteArray.hpp"
#include "SocketImpl.hpp"
#include "SocketOption.hpp"
#include <atomic>

namespace obotcha {

DECLARE_SIMPLE_CLASS(Socket) {
public:
    enum Type {
        Tcp,
        Udp,
        Local
    };

    _Socket(int,InetAddress host,SocketOption option);
    _Socket(int);
    int connect();
    int bind();

    void close();
    bool isClosed();

    int getFd();
    int getType();

    void setInetAddress(InetAddress);
    InetAddress getInetAddress();

    InputStream getInputStream();
    OutputStream getOutputStream();
    
private:
    enum Status {
        Idle = 0,
        Connected,
        Closed,
    };
    int type;

    std::atomic_int mStatus;
    
protected:
    SocketImpl mSock; 
    InputStream mInput;
    OutputStream mOutput;

};

}

#endif