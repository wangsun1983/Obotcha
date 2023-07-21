#ifndef __OBOTCHA_HTTP_SEC_WEBSOCKET_ACCEPT_HPP__
#define __OBOTCHA_HTTP_SEC_WEBSOCKET_ACCEPT_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderSecWebSocketAccept) {

public:
    _HttpHeaderSecWebSocketAccept() = default;
    explicit _HttpHeaderSecWebSocketAccept(String);

    void load(String);

    String get();
    void set(String);

    String toString();

private:
    String accept;
};

}
#endif
