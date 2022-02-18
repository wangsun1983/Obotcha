#ifndef __OBOTCHA_NET_PROTOCOL_HPP__
#define __OBOTCHA_NET_PROTOCOL_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

DECLARE_CLASS(NetProtocol) {

public:
    enum Type {
        Http = 0,
        Https,
        Ws,
        Http_H2,
        Http_H2C
    };
    
};

}

#endif
