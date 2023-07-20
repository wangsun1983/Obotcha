#ifndef __OBOTCHA_HTTP_SEC_WEBSOCKET_VERSION_HPP__
#define __OBOTCHA_HTTP_SEC_WEBSOCKET_VERSION_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderSecWebSocketVersion) {

public:
    _HttpHeaderSecWebSocketVersion();
    explicit _HttpHeaderSecWebSocketVersion(String);

    void load(String);

    int get();
    void set(int);

    String toString();

private:
    int version;
};

}
#endif
