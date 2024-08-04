#include "Inet6Address.hpp"

namespace obotcha {

_Inet6Address::_Inet6Address(String addr, in_port_t port) : _InetAddress(addr, port) {
    mFamily = st(Net)::Family::Ipv6;
}

_Inet6Address::_Inet6Address(in_port_t port) : _InetAddress(port) { 
    mFamily = st(Net)::Family::Ipv6; 
}

String _Inet6Address::getLocalAddress() const { 
    return String::New("::1");
}

} // namespace obotcha