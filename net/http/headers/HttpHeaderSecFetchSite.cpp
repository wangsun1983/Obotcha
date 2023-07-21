#include "HttpHeaderSecFetchSite.hpp"

namespace obotcha {

const String _HttpHeaderSecFetchSite::CrossSite = createString("cross-site");
const String _HttpHeaderSecFetchSite::SameOrigin = createString("same-origin");
const String _HttpHeaderSecFetchSite::SameSite = createString("same-site");
const String _HttpHeaderSecFetchSite::None = createString("none");

_HttpHeaderSecFetchSite::_HttpHeaderSecFetchSite(String s) {
    load(s);
}

void _HttpHeaderSecFetchSite::load(String s) {
    value = s->trim();
}

void _HttpHeaderSecFetchSite::set(String s) {
    load(s);
}

String _HttpHeaderSecFetchSite::get() {
    return value;
}

String _HttpHeaderSecFetchSite::toString() {
    return value;
}


}
