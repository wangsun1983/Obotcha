#include "InetLocalAddress.hpp"

namespace obotcha {

_InetLocalAddress::_InetLocalAddress(String addr) : _InetAddress(addr, -1) {
    mFamily = LOCAL;
}

} // namespace obotcha