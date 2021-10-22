#ifndef __OBOTCHA_HTTP_HEADER_UPGRADE_HPP__
#define __OBOTCHA_HTTP_HEADER_UPGRADE_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderUpgrade) {

public:
    _HttpHeaderUpgrade();
    _HttpHeaderUpgrade(String);

    void import(String);

    String get();
    void set(String);

    String toString();

private:
    String upgrade;
};

}
#endif
