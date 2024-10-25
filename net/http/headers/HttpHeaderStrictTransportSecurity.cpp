#include "HttpHeaderStrictTransportSecurity.hpp"
#include "HttpHeaderContentParser.hpp"
#include "StringBuffer.hpp"

namespace obotcha {

_HttpHeaderStrictTransportSecurity::_HttpHeaderStrictTransportSecurity(String s) {
    load(s->trim());
}

void _HttpHeaderStrictTransportSecurity::load(String s) {
    st(HttpHeaderContentParser)::load(s,[this](String directive,String parameter) {
        if(directive->equalsIgnoreCase("includeSubDomains")) {
            includeSubDomains = true;
        } else if(directive->equalsIgnoreCase("preload")) {
            preload = true;
        } else if(directive->equalsIgnoreCase("max-age")) {
            maxAge = parameter->toBasicLong();
        }
    });
}

String _HttpHeaderStrictTransportSecurity::toString() {
    StringBuffer accept = StringBuffer::New();
    if(maxAge != -1) {
        accept->append("max-age=",String::New(maxAge),";");
    }

    if(preload) {
        accept->append("preload;");
    }
    if(includeSubDomains) {
        accept->append("includeSubDomains;");
    }

    return accept->toString(0,accept->size() - 1);
}

bool _HttpHeaderStrictTransportSecurity::isIncludeSubDomains() const {
    return includeSubDomains;
}

bool _HttpHeaderStrictTransportSecurity::isPreload() const {
    return preload;
}

long _HttpHeaderStrictTransportSecurity::getAge() const {
    return maxAge;
}

void _HttpHeaderStrictTransportSecurity::setIncludeSubDomains(bool v) {
    includeSubDomains = v;
}

void _HttpHeaderStrictTransportSecurity::setPreload(bool v) {
    preload = v;
}

void _HttpHeaderStrictTransportSecurity::setMaxAge(long v) {
    maxAge = v;
}

}
