#ifndef __OBOTCHA_HTTP_SEC_WEBSOCKET_ACCEPT_HPP__
#define __OBOTCHA_HTTP_SEC_WEBSOCKET_ACCEPT_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpSecWebSocketAccept) {

public:
    _HttpSecWebSocketAccept();
    _HttpSecWebSocketAccept(String);

    void import(String);

    String get();
    void set(String);

    String toString();

private:
    String accept;
};

}
#endif
