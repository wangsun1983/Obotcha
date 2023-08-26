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

    enum WindowBitsMode {
        /// Accept any value the remote endpoint offers
        Accept = 1,
        /// Decline any value the remote endpoint offers. Insist on defaults.
        Decline,
        /// Use the largest value common to both offers
        Largest,
        /// Use the smallest value common to both offers
        Smallest
    };
};

}

#endif
