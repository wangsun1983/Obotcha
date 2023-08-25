#ifndef __OBOTCHA_WEBSOCKET_HPP__
#define __OBOTCHA_WEBSOCKET_HPP__

#include "Object.hpp"
#include "Net.hpp"

namespace obotcha {

DECLARE_CLASS(WebSocket) {

public:
    enum class Response {
        Auto = 0,
        Manual
    };
};

}

#endif
