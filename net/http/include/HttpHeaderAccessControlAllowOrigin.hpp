#ifndef __OBOTCHA_HTTP_ACCESS_CONTROL_ALLOW_ORIGIN_HPP__
#define __OBOTCHA_HTTP_ACCESS_CONTROL_ALLOW_ORIGIN_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderAccessControlAllowOrigin) {

public:
    _HttpHeaderAccessControlAllowOrigin() = default;
    explicit _HttpHeaderAccessControlAllowOrigin(String);

    void load(String);

    void set(String);

    String get();

    String toString() override;

private:
    String origin;
};

}
#endif
