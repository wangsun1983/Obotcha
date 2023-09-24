#include "HttpHeaderOrigin.hpp"

namespace obotcha {

_HttpHeaderOrigin::_HttpHeaderOrigin(String s) {
    load(s);
}

void _HttpHeaderOrigin::load(String s) {
    mUrl->load(s);
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