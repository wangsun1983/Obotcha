#ifndef __OBOTCHA_HTTP_HEADER_EXPECT_HPP__
#define __OBOTCHA_HTTP_HEADER_EXPECT_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderExpect) {

public:
    _HttpHeaderExpect() = default;
    explicit _HttpHeaderExpect(String);

    void load(String);

    String get();
    void set(String expect = DefaultExpectCommand);

    String toString() override;

    static const String DefaultExpectCommand;
private:
    String expect;
};

}
#endif
