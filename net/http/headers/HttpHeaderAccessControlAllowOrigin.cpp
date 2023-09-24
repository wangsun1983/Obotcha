#include "HttpHeaderAccessControlAllowOrigin.hpp"

namespace obotcha {

_HttpHeaderAccessControlAllowOrigin::_HttpHeaderAccessControlAllowOrigin(String v) {
    load(v);
}

void _HttpHeaderAccessControlAllowOrigin::load(String v) {
    origin = v->trim();
}

void _HttpHeaderAccessControlAllowOrigin::set(String v) {
    origin = v->trim();
}

String _HttpHeaderAccessControlAllowOrigin::get() {
    return origin;
}

String _HttpHeaderAccessControlAllowOrigin::toString() {
    return origin;
}


}
