#include "HttpHeaderAge.hpp"

namespace obotcha {

_HttpHeaderAge::_HttpHeaderAge(String v) {
    load(v);
}

void _HttpHeaderAge::load(String v) {
    age = v->toBasicInt();
}

void _HttpHeaderAge::set(int v) {
    age = v;
}

int _HttpHeaderAge::get() const {
    return age;
}

String _HttpHeaderAge::toString() {
    return String::New(age);
}

}
