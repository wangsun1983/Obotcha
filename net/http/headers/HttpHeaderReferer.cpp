#include "HttpHeaderReferer.hpp"

namespace obotcha {

_HttpHeaderReferer::_HttpHeaderReferer() {
    mUrl = createHttpUrl();
}

_HttpHeaderReferer::_HttpHeaderReferer(String s) {
    import(s);
}

void _HttpHeaderReferer::import(String s) {
    mUrl->import(s);
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