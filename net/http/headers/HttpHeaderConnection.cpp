#include "HttpHeaderConnection.hpp"

namespace obotcha {


_HttpHeaderConnection::_HttpHeaderConnection() {

}

_HttpHeaderConnection::_HttpHeaderConnection(String v):_HttpHeaderConnection() {
    load(v);
}

void _HttpHeaderConnection::load(String v) {
    type = v->trim();
}

void _HttpHeaderConnection::set(String v) {
    type = v->trim();
}

String _HttpHeaderConnection::get() {
    return type;
}

String _HttpHeaderConnection::toString() {
    return type;
}


}
