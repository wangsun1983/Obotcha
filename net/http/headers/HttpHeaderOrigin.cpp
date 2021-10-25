#include "HttpHeaderOrigin.hpp"

namespace obotcha {

_HttpHeaderOrigin::_HttpHeaderOrigin() {

}

_HttpHeaderOrigin::_HttpHeaderOrigin(String s) {
    origin = s;
}

void _HttpHeaderOrigin::import(String s) {
    origin = s;
}

String _HttpHeaderOrigin::get() {
    return origin;
}

void _HttpHeaderOrigin::set(String s) {
    origin = s;
}

String _HttpHeaderOrigin::toString() {
    return origin;
}

}