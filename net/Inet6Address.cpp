#include "Inet6Address.hpp"

namespace obotcha {

_Inet6Address::_Inet6Address(String addr, int port) : _InetAddress(addr, port) {
    mFamily = IPV6;
}

_Inet6Address::_Inet6Address(int port) : _InetAddress(port) { 
    mFamily = IPV6; 
}

String _Inet6Address::getLocalAddress() { 
    return createString("::1"); 
}

} // namespace obotcha