#include "HttpHeaderAccessControlAllowCredentials.hpp"

namespace obotcha {

_HttpHeaderAccessControlAllowCredentials::_HttpHeaderAccessControlAllowCredentials() {
    allowed = false;
}

_HttpHeaderAccessControlAllowCredentials::_HttpHeaderAccessControlAllowCredentials(String s) {
    import(s);
}

void _HttpHeaderAccessControlAllowCredentials::set(bool v) {
    allowed = v;
}

void _HttpHeaderAccessControlAllowCredentials::import(String s) {
    if(s->trim()->equalsIgnoreCase("true")) {
        allowed = true;
    } else {
        allowed = false;
    }
}

bool _HttpHeaderAccessControlAllowCredentials::get() {
    return allowed;
}

String _HttpHeaderAccessControlAllowCredentials::toString() {
    if(allowed) {
        return createString("true");
    }

    return createString("false");
}

}
