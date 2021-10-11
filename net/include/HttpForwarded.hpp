#ifndef __OBOTCHA_HTTP_FORWARDED_HPP__
#define __OBOTCHA_HTTP_FORWARDED_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpForwarded) {

public:
    _HttpForwarded();
    _HttpForwarded(String);

    void import(String);

    String toString();
    String byIdentity;
    ArrayList<String> forIdentities;
    String host;
    String proto;
};

}
#endif
