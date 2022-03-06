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

#include "InetAddress.hpp"
#include "Log.hpp"
#include "String.hpp"

namespace obotcha {

int _InetAddress::DefaultPort = 8080;

_InetAddress::_InetAddress(int port) {
    mPort = port;
    mAddress = nullptr;
    mFamily = -1;
}

_InetAddress::_InetAddress(String addr, int port) {
    mAddress = addr;
    mPort = port;
    mFamily = -1;
}

_InetAddress::_InetAddress() { 
    mPort = DefaultPort;
    mFamily = -1; 
}

void _InetAddress::setPort(int p) { 
    mPort = p; 
}

int _InetAddress::getPort() { 
    return mPort; 
}

void _InetAddress::setAddress(String addr) {
    if (addr != nullptr) {
        mAddress = addr;
    }
}

String _InetAddress::getAddress() { 
    return mAddress; 
}

int _InetAddress::getFamily() {
    return mFamily;
}

uint64_t _InetAddress::hashcode() {
    return mAddress->hashcode();
}

bool _InetAddress::equals(InetAddress addr) {
    return this->mPort == addr->mPort
           && mFamily == addr->mFamily
           && (mAddress != nullptr)?mAddress->equals(addr->mAddress):addr->mAddress == nullptr;
}

} // namespace obotcha