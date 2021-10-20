#include "HttpIfUnmodifiedSince.hpp"

namespace obotcha {

_HttpIfUnmodifiedSince::_HttpIfUnmodifiedSince() {
    //
}

_HttpIfUnmodifiedSince::_HttpIfUnmodifiedSince(String v) {
    date = createHttpDate(v);
}

void _HttpIfUnmodifiedSince::import(String v) {
    date = createHttpDate(v);
}

HttpDate _HttpIfUnmodifiedSince::get() {
    return date;
}

void _HttpIfUnmodifiedSince::set(HttpDate d) {
    date = d;
}

String _HttpIfUnmodifiedSince::toString() {
    return date->toString();
}


}
