#include "HttpHeaderExpect.hpp"
#include "ProtocolNotSupportException.hpp"

namespace obotcha {

const String _HttpHeaderExpect::DefaultExpectCommand = createString("100-continue");

_HttpHeaderExpect::_HttpHeaderExpect() {

}

_HttpHeaderExpect::_HttpHeaderExpect(String s) {
    import(s);
}

void _HttpHeaderExpect::import(String s) {
    if(!s->trim()->equalsIgnoreCase(DefaultExpectCommand)) {
        Trigger(ProtocolNotSupportException,"only support 100-continue");
    }
    expect = s;
}

String _HttpHeaderExpect::get() {
    return expect;
}

void _HttpHeaderExpect::set(String s) {
    import(s);
}

String _HttpHeaderExpect::toString() {
    return expect;
}

}