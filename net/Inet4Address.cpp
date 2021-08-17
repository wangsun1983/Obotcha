#include <stdio.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <cstring>
#include <netdb.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "Inet4Address.hpp"
#include "String.hpp"
#include "Log.hpp"

namespace obotcha {

_Inet4Address::_Inet4Address(String addr,int port):_InetAddress(addr,port) {
    mType = IPV4;
}

_Inet4Address::_Inet4Address(int port):_InetAddress(getLocalAddress(),port) {
    mType = IPV4;
}

String _Inet4Address::getLocalAddress() {
    return createString("127.0.0.1");
}

}