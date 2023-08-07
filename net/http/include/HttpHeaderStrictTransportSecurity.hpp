#ifndef __OBOTCHA_HTTP_STRICT_TRANSPORT_SECURITY_HPP__
#define __OBOTCHA_HTTP_STRICT_TRANSPORT_SECURITY_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderStrictTransportSecurity) {

public:
    _HttpHeaderStrictTransportSecurity() = default;
    explicit _HttpHeaderStrictTransportSecurity(String);

    void load(String);
    String toString() override;

    bool isIncludeSubDomains() const;
    bool isPreload() const;
    long getAge() const;

    void setIncludeSubDomains(bool);
    void setPreload(bool);
    void setMaxAge(long);

    bool includeSubDomains = false;
    bool preload = false;
    long maxAge = 0;
};

}
#endif
