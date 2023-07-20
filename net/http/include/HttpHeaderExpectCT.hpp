#ifndef __OBOTCHA_HTTP_HEADER_EXPECT_CT_HPP__
#define __OBOTCHA_HTTP_HEADER_EXPECT_CT_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "HttpUrl.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderExpectCT) {

public:
    _HttpHeaderExpectCT();
    explicit _HttpHeaderExpectCT(String);

    void load(String);

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
