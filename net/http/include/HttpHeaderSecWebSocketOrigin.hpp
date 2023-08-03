#ifndef __OBOTCHA_HTTP_SEC_WEBSOCKET_ORIGIN_HPP__
#define __OBOTCHA_HTTP_SEC_WEBSOCKET_ORIGIN_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderSecWebSocketOrigin) {

public:
    _HttpHeaderSecWebSocketOrigin() = default;
    explicit _HttpHeaderSecWebSocketOrigin(String);

    void load(String);

    String get();
    void set(String);

    String toString() override;

private:
    String origin;
};

}
#endif
