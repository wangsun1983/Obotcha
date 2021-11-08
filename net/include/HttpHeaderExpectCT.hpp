#ifndef __OBOTCHA_HTTP_HEADER_EXPECT_CT_HPP__
#define __OBOTCHA_HTTP_HEADER_EXPECT_CT_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "HttpUrl.hpp"
#include "Boolean.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderExpectCT) {

public:
    _HttpHeaderExpectCT();
    _HttpHeaderExpectCT(String);

    void import(String);

    HttpUrl getReportUri();
    int getMaxAge();
    bool isEnforce();

    void setReportUri(HttpUrl);
    void setMaxAge(int);
    void setEnforce(bool);

    String toString();

private:
    HttpUrl reportUri;
    int maxAge;
    bool mEnforce;
};

}
#endif
