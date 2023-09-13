#ifndef __OBOTCHA_HTTP_ACCESS_CONTROL_ALLOW_METHODS_HPP__
#define __OBOTCHA_HTTP_ACCESS_CONTROL_ALLOW_METHODS_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "List.hpp"
#include "HttpMethod.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderAccessControlAllowMethods) {

public:
    _HttpHeaderAccessControlAllowMethods() = default;
    explicit _HttpHeaderAccessControlAllowMethods(String);

    void load(String);

    void add(st(HttpMethod)::Id);

    List<st(HttpMethod)::Id> get() const;

    String toString() override;

private:
    std::vector<st(HttpMethod)::Id> methods;
};

}
#endif
