#ifndef __OBOTCHA_HTTP_ACCESS_CONTROL_MAX_AGE_HPP__
#define __OBOTCHA_HTTP_ACCESS_CONTROL_MAX_AGE_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderAccessControlMaxAge) {

public:
    _HttpHeaderAccessControlMaxAge() = default;
    explicit _HttpHeaderAccessControlMaxAge(String);

    void load(String);

    void set(int);

    int get() const;

    String toString() override;

private:
    int maxage = -1;
};

}
#endif
