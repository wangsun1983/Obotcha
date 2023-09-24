#ifndef __OBOTCHA_HTTP_ACCESS_CONTROL_REQUEST_METHOD_HPP__
#define __OBOTCHA_HTTP_ACCESS_CONTROL_REQUEST_METHOD_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "HttpMethod.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderAccessControlRequestMethod) {

public:
    _HttpHeaderAccessControlRequestMethod() = default;
    explicit _HttpHeaderAccessControlRequestMethod(String);

    void load(String);

    void set(_HttpMethod::Id);

    _HttpMethod::Id get() const;

    String toString() override;

private:
    _HttpMethod::Id method = _HttpMethod::Id::Err;
};

}
#endif
