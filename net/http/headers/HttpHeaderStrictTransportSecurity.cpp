#include "HttpHeaderStrictTransportSecurity.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"

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
    String accept = createString("max-age=")->append(createString(maxAge),";");
    if(preload) {
        accept = accept->append("preload;");
    }
    if(includeSubDomains) {
        accept = accept->append("includeSubDomains;");
    }

    return accept->subString(0,accept->size() - 1);
}

}
