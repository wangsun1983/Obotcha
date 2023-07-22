#ifndef __OBOTCHA_INET_ADDRESS_HPP__
#define __OBOTCHA_INET_ADDRESS_HPP__

#include <arpa/inet.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "Object.hpp"
#include "String.hpp"
#include "OStdReturnValue.hpp"

namespace obotcha {

class _InetAddress;

DECLARE_CLASS(SockAddress) {
public:
    explicit _SockAddress(int family);
    _SockAddress(int family,String address,int port);

    DefRet(int,struct sockaddr *) get();
    int port();
    int family();

    sp<_InetAddress> toInetAddress();

    String toString();

private:
    struct sockaddr_in mSockAddr; //ipv4
    struct sockaddr_in6 mSockAddrV6; //ipv6
    struct sockaddr_un mLocalSockAddr; //local socket 
    int mFamily;
};

DECLARE_CLASS(InetAddress) {

public:
    enum Family {
        IPV4 = 0,
        IPV6,
        LOCAL,
        Max,
    };

    static int kDefaultPort;
    
    _InetAddress(String,int);
    _InetAddress(int);
    _InetAddress();

    int getPort();
    void setPort(int);
    
    String getAddress();
    void setAddress(String);

    SockAddress getSockAddress();

    /*Family:IPV4/IPV6/LOCAL*/
    int getFamily();

    uint64_t hashcode();
    bool equals(Object address) override;

    String toString() override;

protected:
    String mAddress;
    int mPort;
    int mFamily;

    SockAddress mSockAddress;
};

}
#endif
