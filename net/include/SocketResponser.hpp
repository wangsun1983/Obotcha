#ifndef __OBOTCHA_SOCKET_RESPONSER_HPP__
#define __OBOTCHA_SOCKET_RESPONSER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(SocketResponser) {
public:
    _SocketResponser(int fd,String ip = nullptr,int mPort = -1);

    _SocketResponser(String domain,int fd);

    int send(ByteArray);
    
    int getFd();

    String getIp();

    int getPort();

    String getDomain();
private:
    int mFd;

    String mIp;

    int mPort;

    String mDomain;
};

}
#endif
