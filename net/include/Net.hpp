#ifndef __OBOTCHA_NET_HPP__
#define __OBOTCHA_NET_HPP__

#include <netinet/in.h>

#include "Object.hpp"

namespace obotcha {

DECLARE_CLASS(Net) {

public:
    enum class Event {
        Connect = 0,
        Message,
        Disconnect,
        InternalError,
    }; 

    enum class Protocol {
        Tcp = 0,
        Udp,
        Ssl,
        Http,
        Https,
        Ws,
        Http_H2,
        Http_H2C,
        UnKnown
    };

    enum class Family {
        Ipv4 = AF_INET,
        Ipv6 = AF_INET6,
        Local = AF_UNIX,
        Unknow = -1
    };

    static const int DefaultHttpPort = 80;
    static const int DefaultHttpsPort = 443;
};

}
#endif