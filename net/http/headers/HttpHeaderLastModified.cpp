#include "HttpHeaderLastModified.hpp"

namespace obotcha {

_HttpHeaderLastModified::_HttpHeaderLastModified() {

}

_HttpHeaderLastModified::_HttpHeaderLastModified(String s) {
    import(s);
}

void _HttpHeaderLastModified::import(String s) {
    this->date = createHttpDate(s);
}

HttpDate _HttpHeaderLastModified::get() {
    return date;
}

void _HttpHeaderLastModified::set(HttpDate s) {
    date = s;
}

String _HttpHeaderLastModified::toString() {
    return date->toString();
}


}
