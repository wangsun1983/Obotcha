#ifndef __OBOTCHA_HTTP_STRICT_TRANSPORT_SECURITY_HPP__
#define __OBOTCHA_HTTP_STRICT_TRANSPORT_SECURITY_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpStrictTransportSecurity) {

public:
    _HttpStrictTransportSecurity();
    _HttpStrictTransportSecurity(String);

    void import(String);
    
    bool includeSubDomains;
    bool preload;
    long maxAge;

    String toString();

};

}
#endif
