#ifndef __OBOTCHA_HTTP_ACCESS_CONTROL_ALLOW_CREDENTIALS_HPP__
#define __OBOTCHA_HTTP_ACCESS_CONTROL_ALLOW_CREDENTIALS_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderAccessControlAllowCredentials) {

public:
    _HttpHeaderAccessControlAllowCredentials();
    _HttpHeaderAccessControlAllowCredentials(String);

    void import(String);

    bool get();
    
    void set(bool v);

    String toString();

private:
    bool allowed;
};

}
#endif
