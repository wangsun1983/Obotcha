#ifndef __OBOTCHA_HTTP_SEC_WEBSOCKET_ACCEPT_HPP__
#define __OBOTCHA_HTTP_SEC_WEBSOCKET_ACCEPT_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderSecWebSocketAccept) {

public:
    _HttpHeaderSecWebSocketAccept();
    _HttpHeaderSecWebSocketAccept(String);

    void import(String);

    String get();
    void set(String);

    String toString();

private:
    String accept;
};

}
#endif
