#ifndef __OBOTCHA_HTTP_ACCESS_CONTROL_REQUEST_METHOD_HPP__
#define __OBOTCHA_HTTP_ACCESS_CONTROL_REQUEST_METHOD_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpAccessControlRequestMethod) {

public:
    _HttpAccessControlRequestMethod();
    _HttpAccessControlRequestMethod(String);

    void import(String);

    void setMethod(int);

    int getMethod();

    String toString();

private:
    int method;
};

}
#endif
