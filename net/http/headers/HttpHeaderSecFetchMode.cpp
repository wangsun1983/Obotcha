#include "HttpHeaderSecFetchMode.hpp"

namespace obotcha {

const String _HttpHeaderSecFetchMode::Cors = createString("cors");
const String _HttpHeaderSecFetchMode::Navigate = createString("navigate");
const String _HttpHeaderSecFetchMode::NestedNavigate = createString("nasted-navigate");
const String _HttpHeaderSecFetchMode::NoCors = createString("no-cors");
const String _HttpHeaderSecFetchMode::SameOrigin = createString("same-origin");
const String _HttpHeaderSecFetchMode::Websocket = createString("websocket");

_HttpHeaderSecFetchMode::_HttpHeaderSecFetchMode() {

}

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
