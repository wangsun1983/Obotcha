#include "HttpHeaderIfUnmodifiedSince.hpp"

namespace obotcha {

_HttpHeaderIfUnmodifiedSince::_HttpHeaderIfUnmodifiedSince() {
    //
}

_HttpHeaderIfUnmodifiedSince::_HttpHeaderIfUnmodifiedSince(String v) {
    date = createHttpDate(v);
}

void _HttpHeaderIfUnmodifiedSince::load(String v) {
    date = createHttpDate(v);
}

HttpDate _HttpHeaderIfUnmodifiedSince::get() {
    return date;
}

void _HttpHeaderIfUnmodifiedSince::set(HttpDate d) {
    date = d;
}

String _HttpHeaderIfUnmodifiedSince::toString() {
    return date->toString();
}


}
