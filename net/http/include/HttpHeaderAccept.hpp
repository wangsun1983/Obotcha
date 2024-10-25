#ifndef __OBOTCHA_HTTP_HEADER_ACCEPT_HPP__
#define __OBOTCHA_HTTP_HEADER_ACCEPT_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderAcceptItem) {
public:
    explicit _HttpHeaderAcceptItem(String,float w = 1.0);
    String type;
    float weight;
};

DECLARE_CLASS(HttpHeaderAccept) {

public:
    _HttpHeaderAccept() = default;
    explicit _HttpHeaderAccept(String);

    void load(String);
    ArrayList<HttpHeaderAcceptItem> get();
    void add(String,float w = 1.0);
    String toString() override;

private:
    ArrayList<HttpHeaderAcceptItem> accepts = ArrayList<HttpHeaderAcceptItem>::New();
};

}
#endif
