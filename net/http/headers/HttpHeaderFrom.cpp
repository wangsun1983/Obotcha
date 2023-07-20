#include "HttpHeaderFrom.hpp"

namespace obotcha {

_HttpHeaderFrom::_HttpHeaderFrom() {

}

_HttpHeaderFrom::_HttpHeaderFrom(String s) {
    load(s);
}

void _HttpHeaderFrom::load(String s) {
    email = s->trim();
}

String _HttpHeaderFrom::get() {
    return email;
}

void _HttpHeaderFrom::set(String s) {
    email = s->trim();
}

String _HttpHeaderFrom::toString() {
    return email;
}


}
