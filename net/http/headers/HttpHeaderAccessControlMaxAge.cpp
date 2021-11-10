#include "HttpHeaderAccessControlMaxAge.hpp"
#include "HttpMethod.hpp"

namespace obotcha {


_HttpHeaderAccessControlMaxAge::_HttpHeaderAccessControlMaxAge() {

}

_HttpHeaderAccessControlMaxAge::_HttpHeaderAccessControlMaxAge(String v):_HttpHeaderAccessControlMaxAge() {
    import(v);
}

void _HttpHeaderAccessControlMaxAge::import(String v) {
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
