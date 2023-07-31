#include "HttpHeaderContentLocation.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"

namespace obotcha {

_HttpHeaderContentLocation::_HttpHeaderContentLocation(String s):location(s) {
}

void _HttpHeaderContentLocation::load(String s) {
    location = s;
}

String _HttpHeaderContentLocation::get() const {
    return location;
}

void _HttpHeaderContentLocation::set(String v) {
    location = v->trim();
}

String _HttpHeaderContentLocation::toString() {
    return location;
}

}
