#include "HttpHeaderIfModifiedSince.hpp"

namespace obotcha {

_HttpHeaderIfModifiedSince::_HttpHeaderIfModifiedSince(String v) {
    date = HttpDate::New(v);
}

void _HttpHeaderIfModifiedSince::load(String v) {
    date = HttpDate::New(v);
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
