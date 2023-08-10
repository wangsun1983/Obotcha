#include "InetLocalAddress.hpp"
#include "Net.hpp"

namespace obotcha {

_InetLocalAddress::_InetLocalAddress(String addr) : _InetAddress(addr, -1) {
    mFamily = st(Net)::Family::Local;
}

} // namespace obotcha