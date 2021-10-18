#include "HttpAccessControlRequestMethod.hpp"
#include "HttpMethod.hpp"

namespace obotcha {


_HttpAccessControlRequestMethod::_HttpAccessControlRequestMethod() {

}

_HttpAccessControlRequestMethod::_HttpAccessControlRequestMethod(String v):_HttpAccessControlRequestMethod() {
    import(v);
}

void _HttpAccessControlRequestMethod::import(String v) {
    method = st(HttpMethod)::toInt(v);
}

void _HttpAccessControlRequestMethod::setMethod(int v) {
    method = v;
}

int _HttpAccessControlRequestMethod::getMethod() {
    return method;
}

String _HttpAccessControlRequestMethod::toString() {
    return st(HttpMethod)::toString(method);
}

}
