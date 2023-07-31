#ifndef __OBOTCHA_HTTP_CONTENT_TYPE_HPP__
#define __OBOTCHA_HTTP_CONTENT_TYPE_HPP__

//according nginx/conf/mime.types

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderContentType) {

public:
    _HttpHeaderContentType() = default;
    explicit _HttpHeaderContentType(String);

    void load(String value);

    String toString();

    void setType(String);
    void setCharSet(String);
    void setBoundary(String);

    String getType();
    String getCharSet();
    String getBoundary();

private:
    String mContentType = nullptr;
    String mBoundary = nullptr;
    String mCharset = nullptr;

};

}
#endif
