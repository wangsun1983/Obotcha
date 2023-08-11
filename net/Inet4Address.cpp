#include "Inet4Address.hpp"


namespace obotcha {

_Inet4Address::_Inet4Address(String addr, int port) : _InetAddress(addr, port) {
    mFamily = st(Net)::Family::Ipv4;
}

_Inet4Address::_Inet4Address(int port) : _InetAddress(port) { 
    mFamily = st(Net)::Family::Ipv4; 
}

String _Inet4Address::getLocalAddress() const { 
    return createString("127.0.0.1"); 
}

} // namespace obotcha