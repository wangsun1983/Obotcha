#include "HttpHeaderIfModifiedSince.hpp"

namespace obotcha {

_HttpHeaderIfModifiedSince::_HttpHeaderIfModifiedSince() {
    //
}

_HttpHeaderIfModifiedSince::_HttpHeaderIfModifiedSince(String v) {
    date = createHttpDate(v);
}

void _HttpHeaderIfModifiedSince::import(String v) {
    date = createHttpDate(v);
}

HttpDate _HttpHeaderIfModifiedSince::get() {
    return date;
}

void _HttpHeaderIfModifiedSince::set(HttpDate d) {
    date = d;
}

String _HttpHeaderIfModifiedSince::toString() {
    return date->toString();
}

}
