#include "HttpHeaderConnection.hpp"

namespace obotcha {


_HttpHeaderConnection::_HttpHeaderConnection() {

}

_HttpHeaderConnection::_HttpHeaderConnection(String v):_HttpHeaderConnection() {
    import(v);
}

void _HttpHeaderConnection::import(String v) {
    type = v;
}

void _HttpHeaderConnection::set(String v) {
    type = v;
}

String _HttpHeaderConnection::get() {
    return type;
}

String _HttpHeaderConnection::toString() {
    return type;
}


}
