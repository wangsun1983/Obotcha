#ifndef __OBOTCHA_HTTP_ACCEPT_CHARSET_HPP__
#define __OBOTCHA_HTTP_ACCEPT_CHARSET_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpAcceptCharSetItem) {
public:
    _HttpAcceptCharSetItem();
    String type;
    float weight;
};

DECLARE_CLASS(HttpAcceptCharSet) {

public:
    _HttpAcceptCharSet();
    _HttpAcceptCharSet(String);

    void import(String);

    ArrayList<HttpAcceptCharSetItem> getCharSets();

    String toString();

private:
    ArrayList<HttpAcceptCharSetItem> charsets;
};

}
#endif
