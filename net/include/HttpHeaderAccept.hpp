#ifndef __OBOTCHA_HTTP_HEADER_ACCEPT_HPP__
#define __OBOTCHA_HTTP_HEADER_ACCEPT_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderAcceptItem) {
public:
    _HttpHeaderAcceptItem(String,float w = 1.0);
    String type;
    float weight;
};

DECLARE_CLASS(HttpHeaderAccept) {

public:
    _HttpHeaderAccept();
    _HttpHeaderAccept(String);

    void import(String);

    ArrayList<HttpHeaderAcceptItem> get();
    void add(String,float w = 1.0);

    String toString();

private:
    ArrayList<HttpHeaderAcceptItem> accepts;
};

}
#endif
