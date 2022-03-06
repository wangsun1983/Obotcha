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

#include "Inet4Address.hpp"
#include "Log.hpp"
#include "String.hpp"

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