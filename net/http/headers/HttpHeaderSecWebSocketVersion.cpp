#include "HttpHeaderSecWebSocketVersion.hpp"

namespace obotcha {

_HttpHeaderSecWebSocketVersion::_HttpHeaderSecWebSocketVersion(String s) {
    load(s->trim());
}

void _HttpHeaderSecWebSocketVersion::load(String s) {
    version = s->toBasicInt();
}

int _HttpHeaderSecWebSocketVersion::get() const {
    return version;
}

void _HttpHeaderSecWebSocketVersion::set(int s) {
    version = s;
}

String _HttpHeaderSecWebSocketVersion::toString() {
    return createString(version);
}


}