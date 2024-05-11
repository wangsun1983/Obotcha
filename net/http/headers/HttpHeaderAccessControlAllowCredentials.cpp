#include "HttpHeaderAccessControlAllowCredentials.hpp"

namespace obotcha {

_HttpHeaderAccessControlAllowCredentials::_HttpHeaderAccessControlAllowCredentials(String s) {
    load(s);
}

void _HttpHeaderAccessControlAllowCredentials::set(bool v) {
    allowed = v;
}

void _HttpHeaderAccessControlAllowCredentials::load(String s) {
    allowed = s->trim()->equalsIgnoreCase("true");
}

bool _HttpHeaderAccessControlAllowCredentials::get() const {
    return allowed;
}

String _HttpHeaderAccessControlAllowCredentials::toString() {
    return allowed ?String::New("true"):String::New("false");
}

}
