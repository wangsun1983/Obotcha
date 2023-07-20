#ifndef __OBOTCHA_HTTP_HEADER_ACCEPT_CHARSET_HPP__
#define __OBOTCHA_HTTP_HEADER_ACCEPT_CHARSET_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderAcceptCharSetItem) {
public:
    _HttpHeaderAcceptCharSetItem(String,float w = 1.0);
    String type;
    float weight;
};

DECLARE_CLASS(HttpHeaderAcceptCharSet) {

public:
    _HttpHeaderAcceptCharSet();
    _HttpHeaderAcceptCharSet(String);

    void load(String);
    ArrayList<HttpHeaderAcceptCharSetItem> get();
    void add(String,float w = 1.0);
    String toString();

private:
    ArrayList<HttpHeaderAcceptCharSetItem> charsets;
};

}
#endif
