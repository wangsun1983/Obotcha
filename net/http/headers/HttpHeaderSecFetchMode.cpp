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
    import(s);
}

void _HttpHeaderSecFetchMode::import(String s) {
    value = s->trim();
}

void _HttpHeaderSecFetchMode::set(String s) {
    import(s);
}

String _HttpHeaderSecFetchMode::get() {
    return value;
}

String _HttpHeaderSecFetchMode::toString() {
    return value;
}


}
