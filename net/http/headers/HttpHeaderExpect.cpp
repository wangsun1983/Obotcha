#include "HttpHeaderExpect.hpp"
#include "ProtocolNotSupportException.hpp"

namespace obotcha {

const String _HttpHeaderExpect::DefaultExpectCommand = createString("100-continue");

_HttpHeaderExpect::_HttpHeaderExpect(String s) {
    load(s);
}

void _HttpHeaderExpect::load(String s) {
    if(!s->trim()->equalsIgnoreCase(DefaultExpectCommand)) {
        Trigger(ProtocolNotSupportException,"only support 100-continue")
    }
    expect = s;
}

String _HttpHeaderExpect::get() {
    return expect;
}

void _HttpHeaderExpect::set(String s) {
    load(s);
}

String _HttpHeaderExpect::toString() {
    return expect;
}

}