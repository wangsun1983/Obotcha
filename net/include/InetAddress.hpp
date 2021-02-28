#ifndef __OBOTCHA_INET_ADDRESS_HPP__
#define __OBOTCHA_INET_ADDRESS_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

#define MAX_LENGTH 256

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

DECLARE_SIMPLE_CLASS(InetAddress) {

public:
    enum Type {
        IPV4 = 0,
        IPV6,
    };

    static String getHostName();

    static ArrayList<String> getHostByName(String url);
    
    static ArrayList<InetHostAddress> getHostAddress();

    static ArrayList<InetHostMac> getMacAddress();

    void setAddress(String);

    String getAddress();
    
    int type();

private:

    String mHostName;

    String mMac;

    String mAddress;

    int mAddressType;

};

}
#endif
