#include "HttpStrictTransportSecurity.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"

namespace obotcha {

_HttpStrictTransportSecurity::_HttpStrictTransportSecurity() {
    includeSubDomains = false;
    preload = false;
    maxAge = 0;
}

_HttpStrictTransportSecurity::_HttpStrictTransportSecurity(String s) {
    import(s);
}

void _HttpStrictTransportSecurity::import(String s) {
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

String _HttpStrictTransportSecurity::toString() {
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
