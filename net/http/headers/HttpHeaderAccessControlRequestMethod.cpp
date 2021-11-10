#include "HttpHeaderAccessControlRequestMethod.hpp"
#include "HttpMethod.hpp"

namespace obotcha {


_HttpHeaderAccessControlRequestMethod::_HttpHeaderAccessControlRequestMethod() {

}

_HttpHeaderAccessControlRequestMethod::_HttpHeaderAccessControlRequestMethod(String v):_HttpHeaderAccessControlRequestMethod() {
    import(v);
}

void _HttpHeaderAccessControlRequestMethod::import(String v) {
    method = st(HttpMethod)::findId(v->trim());
}

void _HttpHeaderAccessControlRequestMethod::set(int v) {
    method = v;
}

int _HttpHeaderAccessControlRequestMethod::get() {
    return method;
}

String _HttpHeaderAccessControlRequestMethod::toString() {
    return st(HttpMethod)::findString(method);
}

}
