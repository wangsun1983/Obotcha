#include "HttpHeaderAccessControlMaxAge.hpp"
#include "HttpMethod.hpp"

namespace obotcha {

_HttpHeaderAccessControlMaxAge::_HttpHeaderAccessControlMaxAge(String v):_HttpHeaderAccessControlMaxAge() {
    load(v);
}

void _HttpHeaderAccessControlMaxAge::load(String v) {
    maxage = v->toBasicInt();
}

void _HttpHeaderAccessControlMaxAge::set(int v) {
    maxage = v;
}

int _HttpHeaderAccessControlMaxAge::get() {
    return maxage;
}

String _HttpHeaderAccessControlMaxAge::toString() {
    return createString(maxage);
}

}
