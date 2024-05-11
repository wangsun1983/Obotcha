#include "HttpHeaderSecFetchMode.hpp"

namespace obotcha {

const String _HttpHeaderSecFetchMode::Cors = String::New("cors");
const String _HttpHeaderSecFetchMode::Navigate = String::New("navigate");
const String _HttpHeaderSecFetchMode::NestedNavigate = String::New("nasted-navigate");
const String _HttpHeaderSecFetchMode::NoCors = String::New("no-cors");
const String _HttpHeaderSecFetchMode::SameOrigin = String::New("same-origin");
const String _HttpHeaderSecFetchMode::Websocket = String::New("websocket");

_HttpHeaderSecFetchMode::_HttpHeaderSecFetchMode(String s) {
    load(s);
}

void _HttpHeaderSecFetchMode::load(String s) {
    value = s->trim();
}

void _HttpHeaderSecFetchMode::set(String s) {
    load(s);
}

String _HttpHeaderSecFetchMode::get() {
    return value;
}

String _HttpHeaderSecFetchMode::toString() {
    return value;
}


}
