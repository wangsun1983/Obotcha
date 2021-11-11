#ifndef __OBOTCHA_HTTP_SEC_WEBSOCKET_VERSION_HPP__
#define __OBOTCHA_HTTP_SEC_WEBSOCKET_VERSION_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderSecWebSocketVersion) {

public:
    _HttpHeaderSecWebSocketVersion();
    _HttpHeaderSecWebSocketVersion(String);

    void import(String);

    int get();
    void set(int);

    String toString();

private:
    int version;
};

}
#endif
