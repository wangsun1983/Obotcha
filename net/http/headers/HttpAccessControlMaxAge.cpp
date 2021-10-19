#include "HttpAccessControlMaxAge.hpp"
#include "HttpMethod.hpp"

namespace obotcha {


_HttpAccessControlMaxAge::_HttpAccessControlMaxAge() {

}

_HttpAccessControlMaxAge::_HttpAccessControlMaxAge(String v):_HttpAccessControlMaxAge() {
    import(v);
}

void _HttpAccessControlMaxAge::import(String v) {
    maxage = v->toBasicInt();
}

void _HttpAccessControlMaxAge::set(int v) {
    maxage = v;
}

int _HttpAccessControlMaxAge::get() {
    return maxage;
}

String _HttpAccessControlMaxAge::toString() {
    return createString(maxage);
}

}
