#ifndef __OBOTCHA_HTTP_HEADER_ACCEPT_ENCODING_HPP__
#define __OBOTCHA_HTTP_HEADER_ACCEPT_ENCODING_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderAcceptEncodingItem) {
public:
    _HttpHeaderAcceptEncodingItem(String,float w = 1.0);
    String type;
    float weight;
};

DECLARE_CLASS(HttpHeaderAcceptEncoding) {

public:
    _HttpHeaderAcceptEncoding();
    _HttpHeaderAcceptEncoding(String);

    void import(String);

    ArrayList<HttpHeaderAcceptEncodingItem> get();
    void add(String,float w = 1.0);

    String toString();

private:
    ArrayList<HttpHeaderAcceptEncodingItem> encodings;
};

}
#endif