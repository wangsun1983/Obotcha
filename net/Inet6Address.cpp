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

#include "Inet6Address.hpp"
#include "String.hpp"
#include "Log.hpp"

namespace obotcha {

_Inet6Address::_Inet6Address(String addr,int port):_InetAddress(addr,port) {
    mType = IPV6;
}

}