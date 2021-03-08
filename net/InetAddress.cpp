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

String _InetAddress::LocalHost = createString("localhost");

_InetAddress::_InetAddress(String addr,int port) {
    if(addr == nullptr) {
        mAddress = "localhost";
    } else {
        mAddress = addr;
    }
    mPort = port;
}

_InetAddress::_InetAddress() {
    mAddress = "localhost";
    mPort = 8080;
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