#ifndef __OBOTCHA_INET_LOCAL_ADDRESS_HPP__
#define __OBOTCHA_INET_LOCAL_ADDRESS_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(InetLocalAddress) IMPLEMENTS(InetAddress) {
public:
    _InetLocalAddress(String);
};

}
#endif
