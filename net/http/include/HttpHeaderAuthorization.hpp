#ifndef __OBOTCHA_HTTP_AUTHORIZATION_HPP__
#define __OBOTCHA_HTTP_AUTHORIZATION_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderAuthorization) {

public:
    _HttpHeaderAuthorization();
    _HttpHeaderAuthorization(String);

    void import(String);

    String toString();

    String type;
    String credentials; //used for basic
    String username;
    String realm;
    String uri;
    String algorithm;
    String nonce;
    String nc;
    String cnonce;
    String qop;
    String response;
    String opaque;
};

}
#endif
