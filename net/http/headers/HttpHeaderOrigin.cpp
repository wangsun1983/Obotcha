#include "HttpHeaderOrigin.hpp"

namespace obotcha {

_HttpHeaderOrigin::_HttpHeaderOrigin() {
    mUrl = createHttpUrl();
}

_HttpHeaderOrigin::_HttpHeaderOrigin(String s) {
    import(s);
}

void _HttpHeaderOrigin::import(String s) {
    mUrl->import(s);
}

HttpUrl _HttpHeaderOrigin::get() {
    return mUrl;
}

void _HttpHeaderOrigin::set(HttpUrl s) {
    mUrl = s;
}

String _HttpHeaderOrigin::toString() {
    return mUrl->toString();
}

}