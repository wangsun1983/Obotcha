#ifndef __OBOTCHA_INET_ADDRESS_HPP__
#define __OBOTCHA_INET_ADDRESS_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

#define MAX_LENGTH 256

namespace obotcha {

DECLARE_SIMPLE_CLASS(InetAddress) {

public:
    enum Type {
        IPV4 = 0,
        IPV6,
        LOCAL
    };
    
    static String LocalHost;
    
    _InetAddress(String,int);
    _InetAddress(int);
    _InetAddress();

    int getPort();
    void setPort(int);
    
    String getAddress();
    void setAddress(String);

protected:
    String mAddress;

    int mPort;

    int mType;
};

}
#endif
