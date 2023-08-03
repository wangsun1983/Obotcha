#ifndef __OBOTCHA_HTTP_PROXY_AUTHENTICATE_HPP__
#define __OBOTCHA_HTTP_PROXY_AUTHENTICATE_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderProxyAuthenticate) {

public:
    _HttpHeaderProxyAuthenticate() = default;
    explicit _HttpHeaderProxyAuthenticate(String);

    void load(String);

    String toString() override;

    String type;
    String realm;
};

}
#endif
