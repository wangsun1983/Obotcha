#include "HttpSecWebSocketAccept.hpp"

namespace obotcha {

_HttpSecWebSocketAccept::_HttpSecWebSocketAccept() {

}

_HttpSecWebSocketAccept::_HttpSecWebSocketAccept(String s) {
    this->accept = s->trim();
}

void _HttpSecWebSocketAccept::import(String s) {
    accept = s->trim();
}

String _HttpSecWebSocketAccept::get() {
    return accept;
}

void _HttpSecWebSocketAccept::set(String s) {
    accept = s->trim();
}

String _HttpSecWebSocketAccept::toString() {
    return accept;
}


}