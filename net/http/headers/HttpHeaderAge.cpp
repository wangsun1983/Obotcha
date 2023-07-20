#include "HttpHeaderAge.hpp"

namespace obotcha {


_HttpHeaderAge::_HttpHeaderAge() {

}

_HttpHeaderAge::_HttpHeaderAge(String v):_HttpHeaderAge() {
    load(v);
}

void _HttpHeaderAge::load(String v) {
    age = v->toBasicInt();
}

void _HttpHeaderAge::set(int v) {
    age = v;
}

int _HttpHeaderAge::get() {
    return age;
}

String _HttpHeaderAge::toString() {
    return createString(age);
}

}
