#include "HttpIfModifiedSince.hpp"

namespace obotcha {

_HttpIfModifiedSince::_HttpIfModifiedSince() {
    //
}

_HttpIfModifiedSince::_HttpIfModifiedSince(String v) {
    date = createHttpDate(v);
}

void _HttpIfModifiedSince::import(String v) {
    date = createHttpDate(v);
}

HttpDate _HttpIfModifiedSince::get() {
    return date;
}

void _HttpIfModifiedSince::set(HttpDate d) {
    date = d;
}

String _HttpIfModifiedSince::toString() {
    return date->toString();
}


}
