#ifndef __OBOTCHA_HOST_HPP__
#define __OBOTCHA_HOST_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(InetHostAddress) {
public:
    String interface;
    String ip;
};

DECLARE_SIMPLE_CLASS(InetHostMac) {
public:
    String interface;
    String mac;
};

DECLARE_SIMPLE_CLASS(Host) {
public:
    _Host();
    
    String getHostName();
    ArrayList<InetHostAddress> getHostAddress();
    ArrayList<InetHostMac> getMacAddress();
};

}

#endif