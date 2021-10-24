#ifndef __OBOTCHA_HTTP_SEC_WEBSOCKET_PROTOCOL_HPP__
#define __OBOTCHA_HTTP_SEC_WEBSOCKET_PROTOCOL_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpSecWebSocketProtocol) {

public:
    _HttpSecWebSocketProtocol();
    _HttpSecWebSocketProtocol(String);

    void import(String);

    String get();
    void set(String);

    String toString();

private:
    String protocol;
};

}
#endif
