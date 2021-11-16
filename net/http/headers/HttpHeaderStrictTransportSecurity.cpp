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
    import(s->trim());
}

void _HttpHeaderStrictTransportSecurity::import(String s) {
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
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
