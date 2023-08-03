#ifndef __OBOTCHA_HTTP_ACCEPT_RANGES_HPP__
#define __OBOTCHA_HTTP_ACCEPT_RANGES_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderAcceptRanges) {

public:
    _HttpHeaderAcceptRanges() = default;
    explicit _HttpHeaderAcceptRanges(String);

    void load(String);

    void set(String);
    String get();

    String toString() override;

private:
    String range;
};

}
#endif
