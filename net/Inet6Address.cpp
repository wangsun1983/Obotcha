#include "Inet6Address.hpp"
#include "Net.hpp"

namespace obotcha {

_Inet6Address::_Inet6Address(String addr, int port) : _InetAddress(addr, port) {
    mFamily = st(Net)::Family::Ipv6;
}

_Inet6Address::_Inet6Address(int port) : _InetAddress(port) { 
    mFamily = st(Net)::Family::Ipv6; 
}

String _Inet6Address::getLocalAddress() const { 
    return createString("::1"); 
}

} // namespace obotcha