#ifndef __OBOTCHA_HTTP_ACCEPT_HPP__
#define __OBOTCHA_HTTP_ACCEPT_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpAcceptItem) {
public:
    _HttpAcceptItem();
    String type;
    float weight;
};

DECLARE_CLASS(HttpAccept) {

public:
    _HttpAccept();
    _HttpAccept(String);

    void import(String);

    ArrayList<HttpAcceptItem> getAccepts();

    String toString();

private:
    ArrayList<HttpAcceptItem> accepts;
};

}
#endif
