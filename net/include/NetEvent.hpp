#ifndef __OBOTCHA_NET_EVENT_HPP__
#define __OBOTCHA_NET_EVENT_HPP__

#include "Object.hpp"

namespace obotcha {

DECLARE_CLASS(NetEvent) {

public:
    enum Id {
        Connect = 0,
        Message,
        Disconnect,
        InternalError,
    }; 
};

}
#endif