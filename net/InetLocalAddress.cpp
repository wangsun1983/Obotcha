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

#include "InetLocalAddress.hpp"
#include "String.hpp"
#include "Log.hpp"

namespace obotcha {

_InetLocalAddress::_InetLocalAddress(String addr):_InetAddress(addr,-1) {
    mType = LOCAL;
}

}