#ifndef __OBOTCHA_HTTP_HEADER_ETAG_HPP__
#define __OBOTCHA_HTTP_HEADER_ETAG_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderETag) {

public:
    _HttpHeaderETag() = default;
    explicit _HttpHeaderETag(String);

    void load(String);

    bool isWeakCheck();
    String getValue();

    void setWeakCheck(bool);
    void setValue(String);

    String toString() override;

private:
    String mValue;
    bool mWeakCheck = false;
};

}
#endif
