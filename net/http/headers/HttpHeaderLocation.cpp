#include "HttpHeaderLocation.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"

namespace obotcha {

_HttpHeaderLocation::_HttpHeaderLocation() {
}

_HttpHeaderLocation::_HttpHeaderLocation(String s) {
    load(s);
}

void _HttpHeaderLocation::load(String s) {
    location = s->trim();
}

String _HttpHeaderLocation::get() {
    return location;
}

void _HttpHeaderLocation::set(String v) {
    location = v->trim();
}

String _HttpHeaderLocation::toString() {
    return location;
}

}
