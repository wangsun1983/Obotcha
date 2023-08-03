#ifndef __OBOTCHA_HTTP_HEADER_EXPECT_CT_HPP__
#define __OBOTCHA_HTTP_HEADER_EXPECT_CT_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "HttpUrl.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderExpectCT) {

public:
    _HttpHeaderExpectCT() = default;
    explicit _HttpHeaderExpectCT(String);

    void load(String);

    HttpUrl getReportUri() const;
    int getMaxAge() const;
    bool isEnforce() const;

    void setReportUri(HttpUrl);
    void setMaxAge(int);
    void setEnforce(bool);

    String toString() override;

private:
    HttpUrl reportUri = nullptr;
    int maxAge = -1;
    bool mEnforce = false;
};

}
#endif
