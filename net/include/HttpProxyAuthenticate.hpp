#ifndef __OBOTCHA_HTTP_PROXY_AUTHENTICATE_HPP__
#define __OBOTCHA_HTTP_PROXY_AUTHENTICATE_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpProxyAuthenticate) {

public:
    _HttpProxyAuthenticate();
    _HttpProxyAuthenticate(String);

    void import(String);

    String toString();

    String type;
    String realm;
};

}
#endif