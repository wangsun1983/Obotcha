#ifndef __OBOTCHA_HTTP_AUTHORIZATION_HPP__
#define __OBOTCHA_HTTP_AUTHORIZATION_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderAuthorization) {

public:
    _HttpHeaderAuthorization() = default;
    explicit _HttpHeaderAuthorization(String);

    void load(String);

    String toString() override;

    String type = nullptr;
    String credentials = nullptr; //used for basic
    String username = nullptr;
    String realm = nullptr;
    String uri = nullptr;
    String algorithm = nullptr;
    String nonce = nullptr;
    String nc = nullptr;
    String cnonce = nullptr;
    String qop = nullptr;
    String response = nullptr;
    String opaque = nullptr;
};

}
#endif
