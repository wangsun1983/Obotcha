#include "HttpContentLength.hpp"

namespace obotcha {


_HttpContentLength::_HttpContentLength() {

}

_HttpContentLength::_HttpContentLength(int v) {
    length = v;
}

_HttpContentLength::_HttpContentLength(String v):_HttpContentLength() {
    import(v);
}

void _HttpContentLength::import(String v) {
    length = v->toBasicInt();
}

void _HttpContentLength::set(int v) {
    length = v;
}

int _HttpContentLength::get() {
    return length;
}

String _HttpContentLength::toString() {
    return createString(length);
}

}
