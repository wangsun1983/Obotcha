#ifndef __OBOTCHA_HTTP_ACCEPT_ENCODING_HPP__
#define __OBOTCHA_HTTP_ACCEPT_ENCODING_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpAcceptEncodingItem) {
public:
    _HttpAcceptEncodingItem();
    String type;
    float weight;
};

DECLARE_CLASS(HttpAcceptEncoding) {

public:
    _HttpAcceptEncoding();
    _HttpAcceptEncoding(String);

    void import(String);

    ArrayList<HttpAcceptEncodingItem> getEncodings();

    String toString();

private:
    ArrayList<HttpAcceptEncodingItem> encodings;
};

}
#endif
