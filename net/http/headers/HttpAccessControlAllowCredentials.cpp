#include "HttpAccessControlAllowCredentials.hpp"

namespace obotcha {

_HttpAccessControlAllowCredentials::_HttpAccessControlAllowCredentials() {
    allowed = false;
}

_HttpAccessControlAllowCredentials::_HttpAccessControlAllowCredentials(String s) {
    import(s);
}

void _HttpAccessControlAllowCredentials::setAllowed(bool v) {
    allowed = v;
}

void _HttpAccessControlAllowCredentials::import(String s) {
    if(s->equalsIgnoreCase("true")) {
        allowed = true;
    } else {
        allowed = false;
    }
}

bool _HttpAccessControlAllowCredentials::isAllowed() {
    return allowed;
}

String _HttpAccessControlAllowCredentials::toString() {
    if(allowed) {
        return createString("true");
    }

    return createString("false");
}

}
