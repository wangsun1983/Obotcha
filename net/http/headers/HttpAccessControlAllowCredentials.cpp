#include "HttpAccessControlAllowCredentials.hpp"

namespace obotcha {

_HttpAccessControlAllowCredentials::_HttpAccessControlAllowCredentials() {
    allowed = false;
}

_HttpAccessControlAllowCredentials::_HttpAccessControlAllowCredentials(String s) {
    import(s);
}

void _HttpAccessControlAllowCredentials::set(bool v) {
    allowed = v;
}

void _HttpAccessControlAllowCredentials::import(String s) {
    if(s->trim()->equalsIgnoreCase("true")) {
        allowed = true;
    } else {
        allowed = false;
    }
}

bool _HttpAccessControlAllowCredentials::get() {
    return allowed;
}

String _HttpAccessControlAllowCredentials::toString() {
    if(allowed) {
        return createString("true");
    }

    return createString("false");
}

}
