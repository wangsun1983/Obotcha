#ifndef __OBOTCHA_HTTP_AUTHORIZATION_HPP__
#define __OBOTCHA_HTTP_AUTHORIZATION_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpAuthorization) {

public:
    _HttpAuthorization();
    _HttpAuthorization(String);

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
