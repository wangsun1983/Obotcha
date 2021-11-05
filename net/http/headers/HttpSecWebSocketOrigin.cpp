#include "HttpSecWebSocketOrigin.hpp"

namespace obotcha {

_HttpSecWebSocketOrigin::_HttpSecWebSocketOrigin() {

}

_HttpSecWebSocketOrigin::_HttpSecWebSocketOrigin(String s) {
    import(s);
}

void _HttpSecWebSocketOrigin::import(String s) {
    origin = s->trim();
}

String _HttpSecWebSocketOrigin::get() {
    return origin;
}

void _HttpSecWebSocketOrigin::set(String s) {
    origin = s->trim();
}

String _HttpSecWebSocketOrigin::toString() {
    return origin;
}

}