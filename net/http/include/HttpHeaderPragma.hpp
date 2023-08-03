#ifndef __OBOTCHA_HTTP_HEADER_PRAGMA_HPP__
#define __OBOTCHA_HTTP_HEADER_PRAGMA_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderPragma) {

public:
    _HttpHeaderPragma() = default;
    explicit _HttpHeaderPragma(String);

    void load(String);

    String get();
    void set(String);

    String toString() override;

private:
    String pragma;
};

}
#endif
