#include "HttpHeaderSecWebSocketKey.hpp"

namespace obotcha {

_HttpHeaderSecWebSocketKey::_HttpHeaderSecWebSocketKey() {

}

_HttpHeaderSecWebSocketKey::_HttpHeaderSecWebSocketKey(String s) {
    import(s);
}

void _HttpHeaderSecWebSocketKey::import(String s) {
    key = s->trim();
}

String _HttpHeaderSecWebSocketKey::get() {
    return key;
}

void _HttpHeaderSecWebSocketKey::set(String s) {
    key = s->trim();
}

String _HttpHeaderSecWebSocketKey::toString() {
    return key;
}


}