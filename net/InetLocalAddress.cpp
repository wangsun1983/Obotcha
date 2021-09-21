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

#include "InetLocalAddress.hpp"
#include "Log.hpp"
#include "String.hpp"

namespace obotcha {

_InetLocalAddress::_InetLocalAddress(String addr) : _InetAddress(addr, -1) {
    mType = LOCAL;
}

} // namespace obotcha