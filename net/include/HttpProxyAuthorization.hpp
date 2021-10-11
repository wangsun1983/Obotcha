#ifndef __OBOTCHA_HTTP_PROXY_AUTHORIZATION_HPP__
#define __OBOTCHA_HTTP_PROXY_AUTHORIZATION_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpProxyAuthorization) {

public:
    _HttpProxyAuthorization();
    _HttpProxyAuthorization(String);

    void import(String);

    String type;
    String credentials;
    
    String toString();
};

}
#endif
