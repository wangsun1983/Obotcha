#ifndef __OBOTCHA_SOCKET_HPP__
#define __OBOTCHA_SOCKET_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ByteArray.hpp"
#include "SocketImpl.hpp"
#include "SocketOption.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Socket) {
public:
    enum Type {
        Tcp,
        Udp
    };

    _Socket(int,InetAddress host, int port,SocketOption option);
    int connect();

    void close();
    int getFd();
    int getType();

    //remove function
    int send(ByteArray) {return 0;}
    int send(ByteArray,int) {return 0;}
    _Socket(int){}

    InputStream getInputStream();
    OutputStream getOutputStream();
    
private:
    enum Status {
        Idle = 0,
        Connected,
        Closed,
    };

    SocketImpl mSock; 
    int type;  
};

}

#endif