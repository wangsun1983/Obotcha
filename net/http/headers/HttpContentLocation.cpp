#include "HttpContentLocation.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"

namespace obotcha {

_HttpContentLocation::_HttpContentLocation() {
}

_HttpContentLocation::_HttpContentLocation(String s) {
    location = s;
}

void _HttpContentLocation::import(String s) {
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        location = directive;
    });
}

String _HttpContentLocation::get() {
    return location;
}

void _HttpContentLocation::set(String v) {
    location = v;
}

String _HttpContentLocation::toString() {
    return location;
}

}
