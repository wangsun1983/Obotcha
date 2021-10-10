#ifndef __OBOTCHA_HTTP_CONTENT_TYPE_HPP__
#define __OBOTCHA_HTTP_CONTENT_TYPE_HPP__

//according nginx/conf/mime.types

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "ByteArray.hpp"
#include "HttpCookie.hpp"
#include "Mutex.hpp"
#include "File.hpp"

namespace obotcha {

DECLARE_CLASS(HttpContentType) {

public:
    _HttpContentType();
    _HttpContentType(String);

    void import(String value);

    String toString();

    void setType(String);
    void setCharSet(String);
    void setBoundary(String);

    String getType();
    String getCharSet();
    String getBoundary();


private:
    String mContentType;
    String mBoundary;
    String mCharset;

};

}
#endif
