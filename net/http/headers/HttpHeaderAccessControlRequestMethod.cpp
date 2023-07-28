#include "HttpHeaderAccessControlRequestMethod.hpp"
#include "HttpMethod.hpp"

namespace obotcha {

_HttpHeaderAccessControlRequestMethod::_HttpHeaderAccessControlRequestMethod(String v):_HttpHeaderAccessControlRequestMethod() {
    load(v);
}

void _HttpHeaderAccessControlRequestMethod::load(String v) {
    method = st(HttpMethod)::toId(v->trim());
}

void _HttpHeaderAccessControlRequestMethod::set(int v) {
    method = v;
}

int _HttpHeaderAccessControlRequestMethod::get() const {
    return method;
}

String _HttpHeaderAccessControlRequestMethod::toString() {
    return st(HttpMethod)::toString(method);
}

}
