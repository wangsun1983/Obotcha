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

void _HttpAccessControlMaxAge::setMaxAge(int v) {
    maxage = v;
}

int _HttpAccessControlMaxAge::getMaxAge() {
    return maxage;
}

String _HttpAccessControlMaxAge::toString() {
    return createString(maxage);
}

}
