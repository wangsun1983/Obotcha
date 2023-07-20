#ifndef __OBOTCHA_HTTP_STRICT_TRANSPORT_SECURITY_HPP__
#define __OBOTCHA_HTTP_STRICT_TRANSPORT_SECURITY_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderStrictTransportSecurity) {

public:
    _HttpHeaderStrictTransportSecurity();
    explicit _HttpHeaderStrictTransportSecurity(String);

    void load(String);
    
    bool includeSubDomains;
    bool preload;
    long maxAge;

    String toString();

};

}
#endif
