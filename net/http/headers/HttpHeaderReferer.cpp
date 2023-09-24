#include "HttpHeaderReferer.hpp"

namespace obotcha {

_HttpHeaderReferer::_HttpHeaderReferer(String s) {
    load(s);
}

void _HttpHeaderReferer::load(String s) {
    mUrl->load(s);
}

HttpUrl _HttpHeaderReferer::get() {
    return mUrl;
}

void _HttpHeaderReferer::set(HttpUrl s) {
    mUrl = s;
}

String _HttpHeaderReferer::toString() {
    return mUrl->toString();
}

}