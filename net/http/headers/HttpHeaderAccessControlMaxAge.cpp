#include "HttpHeaderAccessControlMaxAge.hpp"

namespace obotcha {

_HttpHeaderAccessControlMaxAge::_HttpHeaderAccessControlMaxAge(String v) {
    load(v);
}

void _HttpHeaderAccessControlMaxAge::load(String v) {
    maxage = v->toBasicInt();
}

void _HttpHeaderAccessControlMaxAge::set(int v) {
    maxage = v;
}

int _HttpHeaderAccessControlMaxAge::get() const {
    return maxage;
}

String _HttpHeaderAccessControlMaxAge::toString() {
    return String::New(maxage);
}

}
