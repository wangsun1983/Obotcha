#include "HttpIfRange.hpp"

namespace obotcha {

_HttpIfRange::_HttpIfRange() {
    //
}

_HttpIfRange::_HttpIfRange(String v) {
    date = createHttpDate(v);
}

void _HttpIfRange::import(String v) {
    date = createHttpDate(v);
}

HttpDate _HttpIfRange::get() {
    return date;
}

void _HttpIfRange::set(HttpDate d) {
    date = d;
}

String _HttpIfRange::toString() {
    return date->toString();
}


}
