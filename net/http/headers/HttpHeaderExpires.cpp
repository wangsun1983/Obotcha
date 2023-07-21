#include "HttpHeaderExpires.hpp"

namespace obotcha {

_HttpHeaderExpires::_HttpHeaderExpires(String s) {
    load(s);
}

void _HttpHeaderExpires::load(String s) {
    this->date = createHttpDate(s);
}

HttpDate _HttpHeaderExpires::get() {
    return date;
}

void _HttpHeaderExpires::set(HttpDate s) {
    date = s;
}

String _HttpHeaderExpires::toString() {
    return date->toString();
}


}
