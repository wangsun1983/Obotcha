#include "HttpSecWebSocketKey.hpp"

namespace obotcha {

_HttpSecWebSocketKey::_HttpSecWebSocketKey() {

}

_HttpSecWebSocketKey::_HttpSecWebSocketKey(String s) {
    import(s);
}

void _HttpSecWebSocketKey::import(String s) {
    key = s->trim();
}

String _HttpSecWebSocketKey::get() {
    return key;
}

void _HttpSecWebSocketKey::set(String s) {
    key = s->trim();
}

String _HttpSecWebSocketKey::toString() {
    return key;
}


}