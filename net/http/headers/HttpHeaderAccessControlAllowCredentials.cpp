#include "HttpHeaderAccessControlAllowCredentials.hpp"

namespace obotcha {

_HttpHeaderAccessControlAllowCredentials::_HttpHeaderAccessControlAllowCredentials() {
    allowed = false;
}

_HttpHeaderAccessControlAllowCredentials::_HttpHeaderAccessControlAllowCredentials(String s) {
    load(s);
}

void _HttpHeaderAccessControlAllowCredentials::set(bool v) {
    allowed = v;
}

void _HttpHeaderAccessControlAllowCredentials::load(String s) {
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
    return (allowed)?createString("true"):createString("false");
}

}
