#include "HttpHeaderLocation.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"

namespace obotcha {

_HttpHeaderLocation::_HttpHeaderLocation() {
}

_HttpHeaderLocation::_HttpHeaderLocation(String s) {
    import(s);
}

void _HttpHeaderLocation::import(String s) {
    //st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        location = s->trim();
    //});
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