#ifndef __OBOTCHA_HTTP_SEC_WEBSOCKET_ORIGIN_HPP__
#define __OBOTCHA_HTTP_SEC_WEBSOCKET_ORIGIN_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderSecWebSocketOrigin) {

public:
    _HttpHeaderSecWebSocketOrigin();
    _HttpHeaderSecWebSocketOrigin(String);

    void import(String);

    String get();
    void set(String);

    String toString();

private:
    String origin;
};

}
#endif
