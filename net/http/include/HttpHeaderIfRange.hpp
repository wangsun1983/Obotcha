#ifndef __OBOTCHA_HTTP_IF_RANGE_HPP__
#define __OBOTCHA_HTTP_IF_RANGE_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "HttpDate.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderIfRange) {

public:
    _HttpHeaderIfRange() = default;
    explicit _HttpHeaderIfRange(String);

    void load(String);

    HttpDate getDate() const;
    String getTag() const;

    void set(HttpDate);
    void set(String);

    String toString() override;

private:
    HttpDate date = nullptr;
    String tag = nullptr;
};

}
#endif
