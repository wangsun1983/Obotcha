#ifndef __OBOTCHA_HTTP_HEADER_EXPECT_HPP__
#define __OBOTCHA_HTTP_HEADER_EXPECT_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderExpect) {

public:
    _HttpHeaderExpect();
    _HttpHeaderExpect(String);

    void import(String);

    String get();
    void set(String expect = DefaultExpectCommand);

    String toString();

    static const String DefaultExpectCommand;
private:
    String expect;
};

}
#endif
