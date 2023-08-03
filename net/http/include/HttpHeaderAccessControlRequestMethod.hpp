#ifndef __OBOTCHA_HTTP_ACCESS_CONTROL_REQUEST_METHOD_HPP__
#define __OBOTCHA_HTTP_ACCESS_CONTROL_REQUEST_METHOD_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderAccessControlRequestMethod) {

public:
    _HttpHeaderAccessControlRequestMethod() = default;
    explicit _HttpHeaderAccessControlRequestMethod(String);

    void load(String);

    void set(int);

    int get() const;

    String toString() override;

private:
    int method;
};

}
#endif
