#include "HttpAge.hpp"

namespace obotcha {


_HttpAge::_HttpAge() {

}

_HttpAge::_HttpAge(String v):_HttpAge() {
    import(v);
}

void _HttpAge::import(String v) {
    age = v->toBasicInt();
}

void _HttpAge::set(int v) {
    age = v;
}

int _HttpAge::get() {
    return age;
}

String _HttpAge::toString() {
    return createString(age);
}

}
