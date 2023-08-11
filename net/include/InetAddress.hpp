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
#include "Net.hpp"

namespace obotcha {

class _InetAddress;

DECLARE_CLASS(SockAddress) {
public:
    explicit _SockAddress(st(Net)::Family family);
    _SockAddress(st(Net)::Family family,String address,int port);

    DefRet(int,struct sockaddr *) get();
    int port() const;
    int family() const;

    sp<_InetAddress> toInetAddress();

    String toString() override;

private:
    struct sockaddr_in mSockAddr; //ipv4
    struct sockaddr_in6 mSockAddrV6; //ipv6
    struct sockaddr_un mLocalSockAddr; //local socket 
    st(Net)::Family mFamily;
};

DECLARE_CLASS(InetAddress) {
public:
    static int kDefaultPort;
    
    _InetAddress(String,int);
    explicit _InetAddress(int);
    _InetAddress() = default;

    int getPort();
    void setPort(int);
    
    String getAddress();
    void setAddress(String);

    SockAddress getSockAddress();

    /*Family:IPV4/IPV6/LOCAL*/
    st(Net)::Family getFamily();

    uint64_t hashcode() const override;
    bool equals(Object address) override;

    String toString() override;

protected:
    String mAddress = nullptr;
    int mPort = kDefaultPort;
    st(Net)::Family mFamily = st(Net)::Family::Unknow;
    SockAddress mSockAddress;
};

}
#endif
