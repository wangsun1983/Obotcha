#include "HttpHeaderAccessControlRequestMethod.hpp"

namespace obotcha {

_HttpHeaderAccessControlRequestMethod::_HttpHeaderAccessControlRequestMethod(String v) {
    load(v);
}

void _HttpHeaderAccessControlRequestMethod::load(String v) {
    method = st(HttpMethod)::toId(v->trim());
}

void _HttpHeaderAccessControlRequestMethod::set(_HttpMethod::Id v) {
    method = v;
}

_HttpMethod::Id _HttpHeaderAccessControlRequestMethod::get() const {
    return method;
}

String _HttpHeaderAccessControlRequestMethod::toString() {
    return st(HttpMethod)::toString(method);
}

}
