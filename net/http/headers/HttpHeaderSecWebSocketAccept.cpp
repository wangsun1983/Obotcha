#include "HttpHeaderSecWebSocketAccept.hpp"

namespace obotcha {

_HttpHeaderSecWebSocketAccept::_HttpHeaderSecWebSocketAccept() {

}

_HttpHeaderSecWebSocketAccept::_HttpHeaderSecWebSocketAccept(String s) {
    this->accept = s->trim();
}

void _HttpHeaderSecWebSocketAccept::import(String s) {
    accept = s->trim();
}

String _HttpHeaderSecWebSocketAccept::get() {
    return accept;
}

void _HttpHeaderSecWebSocketAccept::set(String s) {
    accept = s->trim();
}

String _HttpHeaderSecWebSocketAccept::toString() {
    return accept;
}


}