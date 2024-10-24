#ifndef __OBOTCHA_INET6_ADDRESS_HPP__
#define __OBOTCHA_INET6_ADDRESS_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "InetAddress.hpp"

namespace obotcha {

DECLARE_CLASS(Inet6Address) IMPLEMENTS(InetAddress) {
public:
    _Inet6Address(String,in_port_t);
    explicit _Inet6Address(in_port_t);
    String getLocalAddress() const;
};

}
#endif
