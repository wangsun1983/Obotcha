#ifndef __OBOTCHA_INET4_ADDRESS_HPP__
#define __OBOTCHA_INET4_ADDRESS_HPP__

#include "Object.hpp"
#include "InetAddress.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(Inet4Address) IMPLEMENTS(InetAddress) {
  public:
    _Inet4Address(String, in_port_t);
    explicit _Inet4Address(in_port_t);

    String getLocalAddress() const;
};

} // namespace obotcha
#endif
