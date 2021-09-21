#ifndef __OBOTCHA_INET4_ADDRESS_HPP__
#define __OBOTCHA_INET4_ADDRESS_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "InetAddress.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(Inet4Address) IMPLEMENTS(InetAddress) {
  public:
    _Inet4Address(String, int);
    _Inet4Address(int);

    String getLocalAddress();
};

} // namespace obotcha
#endif
