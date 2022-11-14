#ifndef __OBOTCHA_HOST_HPP__
#define __OBOTCHA_HOST_HPP__

#include "Object.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HostAddress) {
public:
    String interface;
    String ip;
    int type;
};

DECLARE_CLASS(HostMac) {
public:
    String interface;
    String mac;
};

DECLARE_CLASS(Host) {
public:
    _Host();
    
    String getName();
    ArrayList<HostAddress> getAddresses();
    ArrayList<HostMac> getMacAddresses();
};

}

#endif