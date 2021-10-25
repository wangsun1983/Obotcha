#include "HttpSecWebSocketAccept.hpp"

namespace obotcha {

_HttpSecWebSocketAccept::_HttpSecWebSocketAccept() {

}

_HttpSecWebSocketAccept::_HttpSecWebSocketAccept(String s) {
    this->accept = s;
}

void _HttpSecWebSocketAccept::import(String s) {
    accept = s;
}

String _HttpSecWebSocketAccept::get() {
    return accept;
}

void _HttpSecWebSocketAccept::set(String s) {
    accept = s;
}

String _HttpSecWebSocketAccept::toString() {
    return accept;
}


}