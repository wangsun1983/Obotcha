#include "HttpHeaderContentLength.hpp"

namespace obotcha {


_HttpHeaderContentLength::_HttpHeaderContentLength() {

}

_HttpHeaderContentLength::_HttpHeaderContentLength(int v) {
    length = v;
}

_HttpHeaderContentLength::_HttpHeaderContentLength(String v):_HttpHeaderContentLength() {
    import(v);
}

void _HttpHeaderContentLength::import(String v) {
    length = v->toBasicInt();
}

void _HttpHeaderContentLength::set(int v) {
    length = v;
}

int _HttpHeaderContentLength::get() {
    return length;
}

String _HttpHeaderContentLength::toString() {
    return createString(length);
}

}
