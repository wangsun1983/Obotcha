#include "HttpHeaderDate.hpp"

namespace obotcha {

_HttpHeaderDate::_HttpHeaderDate() {

}

_HttpHeaderDate::_HttpHeaderDate(String s) {
    import(s);
}

void _HttpHeaderDate::import(String s) {
    this->date = createHttpDate(s);
}

HttpDate _HttpHeaderDate::get() {
    return date;
}

void _HttpHeaderDate::set(HttpDate s) {
    date = s;
}

String _HttpHeaderDate::toString() {
    return date->toString();
}


}
