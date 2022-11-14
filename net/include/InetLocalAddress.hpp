#ifndef __OBOTCHA_INET_LOCAL_ADDRESS_HPP__
#define __OBOTCHA_INET_LOCAL_ADDRESS_HPP__

#include "Object.hpp"
#include "InetAddress.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(InetLocalAddress) IMPLEMENTS(InetAddress) {
  public:
    _InetLocalAddress(String);
};

} // namespace obotcha
#endif
