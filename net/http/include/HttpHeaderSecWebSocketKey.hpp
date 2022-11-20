#ifndef __OBOTCHA_HTTP_SEC_WEB_SOCKET_KEY_HPP__
#define __OBOTCHA_HTTP_SEC_WEB_SOCKET_KEY_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderSecWebSocketKey) {

public:
    _HttpHeaderSecWebSocketKey();
    _HttpHeaderSecWebSocketKey(String);

    void import(String);

    String get();
    void set(String);

    String toString();

private:
    String key;
};

}
#endif
