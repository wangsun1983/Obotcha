#include "HttpHeaderStrictTransportSecurity.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"
#include "StringBuffer.hpp"

namespace obotcha {

_HttpHeaderStrictTransportSecurity::_HttpHeaderStrictTransportSecurity() {
    includeSubDomains = false;
    preload = false;
    maxAge = 0;
}

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
    StringBuffer accept = createStringBuffer();
    if(maxAge != -1) {
        accept->append("max-age=",createString(maxAge),";");
    }

    if(preload) {
        accept->append("preload;");
    }
    if(includeSubDomains) {
        accept->append("includeSubDomains;");
    }

    return accept->toString(0,accept->size() - 1);
}

}
