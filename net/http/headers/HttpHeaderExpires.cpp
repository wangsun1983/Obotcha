#include "HttpHeaderExpires.hpp"

namespace obotcha {

_HttpHeaderExpires::_HttpHeaderExpires() {

}

_HttpHeaderExpires::_HttpHeaderExpires(String s) {
    import(s);
}

void _HttpHeaderExpires::import(String s) {
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
