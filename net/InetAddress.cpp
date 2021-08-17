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

#include "InetAddress.hpp"
#include "String.hpp"
#include "Log.hpp"

namespace obotcha {

int _InetAddress::DefaultPort = 8080;

_InetAddress::_InetAddress(int port) {
    mPort = port;
}

_InetAddress::_InetAddress(String addr,int port) {
    mAddress = addr;
    mPort = port;
}

_InetAddress::_InetAddress() {
    mPort = DefaultPort;
}

void _InetAddress::setPort(int p) {
    mPort = p;
}

int _InetAddress::getPort() {
    return mPort;
}

void _InetAddress::setAddress(String addr) {
    if(addr != nullptr) {
        mAddress = addr;
    }
}

String _InetAddress::getAddress() {
    return mAddress;
}

}