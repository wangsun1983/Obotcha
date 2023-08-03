#ifndef __OBOTCHA_HTTP_HEADER_FROM_HPP__
#define __OBOTCHA_HTTP_HEADER_FROM_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderFrom) {

public:
    _HttpHeaderFrom() = default;
    explicit _HttpHeaderFrom(String);

    void load(String);

    String get();
    void set(String);

    String toString() override;

private:
    String email;
};

}
#endif
