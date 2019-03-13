#ifndef __INET_ADDRESS_HPP__
#define __INET_ADDRESS_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

#define MAX_LENGTH 256

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
    
    static String getHostName();
    
    static ArrayList<InetHostAddress> getHostAddress();

    static ArrayList<InetHostMac> getMacAddress();

private:

    String mHostName;

    String mMac;

};

#endif
