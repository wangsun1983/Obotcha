#ifndef __OBOTCHA_HTTP_PROXY_AUTHORIZATION_HPP__
#define __OBOTCHA_HTTP_PROXY_AUTHORIZATION_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderProxyAuthorization) {

public:
    _HttpHeaderProxyAuthorization() = default;
    explicit _HttpHeaderProxyAuthorization(String);

    void load(String);

    String type;
    String credentials;
    
    String toString();
};

}
#endif
