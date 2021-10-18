#ifndef __OBOTCHA_HTTP_ACCESS_CONTROL_ALLOW_ORIGIN_HPP__
#define __OBOTCHA_HTTP_ACCESS_CONTROL_ALLOW_ORIGIN_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpAccessControlAllowOrigin) {

public:
    _HttpAccessControlAllowOrigin();
    _HttpAccessControlAllowOrigin(String);

    void import(String);

    void setOrigin(String);

    String getOrigin();

    String toString();

private:
    String origin;
};

}
#endif
