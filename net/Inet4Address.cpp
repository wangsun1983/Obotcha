#include "Inet4Address.hpp"

namespace obotcha {

_Inet4Address::_Inet4Address(String addr, int port) : _InetAddress(addr, port) {
    mFamily = IPV4;
}

_Inet4Address::_Inet4Address(int port) : _InetAddress(port) { 
    mFamily = IPV4; 
}

String _Inet4Address::getLocalAddress() { 
    return createString("127.0.0.1"); 
}

} // namespace obotcha