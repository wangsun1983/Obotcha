#include <arpa/inet.h>
#include <cstring>
#include <ifaddrs.h>
#include <net/if.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "Inet6Address.hpp"
#include "Log.hpp"
#include "String.hpp"

namespace obotcha {

_Inet6Address::_Inet6Address(String addr, int port) : _InetAddress(addr, port) {
    mType = IPV6;
}

_Inet6Address::_Inet6Address(int port) : _InetAddress(port) { 
    mType = IPV6; 
}

String _Inet6Address::getLocalAddress() { 
    return createString("::1"); 
}

} // namespace obotcha