#ifndef __OBOTCHA_HTTP_ACCEPT_ENCODING_HPP__
#define __OBOTCHA_HTTP_ACCEPT_ENCODING_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpAcceptEncodingItem) {
public:
    _HttpAcceptEncodingItem(String,float w = 1.0);
    String type;
    float weight;
};

DECLARE_CLASS(HttpAcceptEncoding) {

public:
    _HttpAcceptEncoding();
    _HttpAcceptEncoding(String);

    void import(String);

    ArrayList<HttpAcceptEncodingItem> get();
    void add(String,float w = 1.0);

    String toString();

private:
    ArrayList<HttpAcceptEncodingItem> encodings;
};

}
#endif
