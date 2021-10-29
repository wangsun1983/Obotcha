#include "HttpAccessControlRequestMethod.hpp"
#include "HttpMethod.hpp"

namespace obotcha {


_HttpAccessControlRequestMethod::_HttpAccessControlRequestMethod() {

}

_HttpAccessControlRequestMethod::_HttpAccessControlRequestMethod(String v):_HttpAccessControlRequestMethod() {
    import(v);
}

void _HttpAccessControlRequestMethod::import(String v) {
    method = st(HttpMethod)::findId(v);
}

void _HttpAccessControlRequestMethod::set(int v) {
    method = v;
}

int _HttpAccessControlRequestMethod::get() {
    return method;
}

String _HttpAccessControlRequestMethod::toString() {
    return st(HttpMethod)::findString(method);
}

}
