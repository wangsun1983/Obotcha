#include "HttpHeaderSecWebSocketOrigin.hpp"

namespace obotcha {

_HttpHeaderSecWebSocketOrigin::_HttpHeaderSecWebSocketOrigin(String s) {
    load(s);
}

void _HttpHeaderSecWebSocketOrigin::load(String s) {
    origin = s->trim();
}

String _HttpHeaderSecWebSocketOrigin::get() {
    return origin;
}

void _HttpHeaderSecWebSocketOrigin::set(String s) {
    origin = s->trim();
}

String _HttpHeaderSecWebSocketOrigin::toString() {
    return origin;
}

}