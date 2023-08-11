#ifndef __OBOTCHA_HOST_HPP__
#define __OBOTCHA_HOST_HPP__

#include "Object.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "Net.hpp"

namespace obotcha {

DECLARE_CLASS(HostAddress) {
public:
    String interface;
    String ip;
    st(Net)::Family type;
};

DECLARE_CLASS(HostMac) {
public:
    String interface;
    String mac;
};

DECLARE_CLASS(Host) {
public:
    _Host() = default;
    
    String getName() const;
    ArrayList<HostAddress> getAddresses() const;
    ArrayList<HostMac> getMacAddresses() const;
};

}

#endif