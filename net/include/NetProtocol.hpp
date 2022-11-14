#ifndef __OBOTCHA_NET_PROTOCOL_HPP__
#define __OBOTCHA_NET_PROTOCOL_HPP__

#include "Object.hpp"

namespace obotcha {

DECLARE_CLASS(NetProtocol) {

public:
    enum Type {
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
    
    static const int DefaultHttpPort = 80;
    static const int DefaultHttpsPort = 443;
};

}

#endif
