#ifndef __OBOTCHA_HTTP_ACCESS_CONTROL_ALLOW_CREDENTIALS_HPP__
#define __OBOTCHA_HTTP_ACCESS_CONTROL_ALLOW_CREDENTIALS_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderAccessControlAllowCredentials) {

public:
    _HttpHeaderAccessControlAllowCredentials() = default;
    explicit _HttpHeaderAccessControlAllowCredentials(String);

    void load(String);

    bool get() const;
    
    void set(bool v);

    String toString();

private:
    bool allowed = false;
};

}
#endif
