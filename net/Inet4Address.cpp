#include "Inet4Address.hpp"


namespace obotcha {

_Inet4Address::_Inet4Address(String addr, in_port_t port) : _InetAddress(addr, port) {
    mFamily = st(Net)::Family::Ipv4;
}

_Inet4Address::_Inet4Address(in_port_t port) : _InetAddress(port) { 
    mFamily = st(Net)::Family::Ipv4; 
}

String _Inet4Address::getLocalAddress() const { 
    return String::New("127.0.0.1"); 
}

} // namespace obotcha