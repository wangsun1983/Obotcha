#ifndef __OBOTCHA_INET4_ADDRESS_HPP__
#define __OBOTCHA_INET4_ADDRESS_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Inet4Address) IMPLEMENTS(InetAddress) {
public:
    _Inet4Address(String,int);
    _Inet4Address(int);
};

}
#endif
