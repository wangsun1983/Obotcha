#ifndef __OBOTCHA_INET6_ADDRESS_HPP__
#define __OBOTCHA_INET6_ADDRESS_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Inet6Address) IMPLEMENTS(InetAddress) {
public:
    _Inet6Address(String,int);
    _Inet6Address(int);
};

}
#endif
