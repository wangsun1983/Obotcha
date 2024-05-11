#include "HttpHeaderSecFetchSite.hpp"

namespace obotcha {

const String _HttpHeaderSecFetchSite::CrossSite = String::New("cross-site");
const String _HttpHeaderSecFetchSite::SameOrigin = String::New("same-origin");
const String _HttpHeaderSecFetchSite::SameSite = String::New("same-site");
const String _HttpHeaderSecFetchSite::None = String::New("none");

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
