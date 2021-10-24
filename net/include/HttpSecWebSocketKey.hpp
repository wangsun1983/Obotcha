#ifndef __OBOTCHA_HTTP_SEC_WEB_SOCKET_KEY_HPP__
#define __OBOTCHA_HTTP_SEC_WEB_SOCKET_KEY_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpSecWebSocketKey) {

public:
    _HttpSecWebSocketKey();
    _HttpSecWebSocketKey(String);

    void import(String);

    String get();
    void set(String);

    String toString();

private:
    String key;
};

}
#endif
