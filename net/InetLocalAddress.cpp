#include "InetLocalAddress.hpp"
#include "Net.hpp"

namespace obotcha {

_InetLocalAddress::_InetLocalAddress(String addr) : _InetAddress(addr, 0) {
    mFamily = st(Net)::Family::Local;
}

} // namespace obotcha