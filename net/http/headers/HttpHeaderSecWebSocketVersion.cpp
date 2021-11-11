#include "HttpHeaderSecWebSocketVersion.hpp"

namespace obotcha {

_HttpHeaderSecWebSocketVersion::_HttpHeaderSecWebSocketVersion() {
    version = 13;
}

_HttpHeaderSecWebSocketVersion::_HttpHeaderSecWebSocketVersion(String s):_HttpHeaderSecWebSocketVersion() {
    import(s->trim());
}

void _HttpHeaderSecWebSocketVersion::import(String s) {
    version = s->toBasicInt();
}

int _HttpHeaderSecWebSocketVersion::get() {
    return version;
}

void _HttpHeaderSecWebSocketVersion::set(int s) {
    version = s;
}

String _HttpHeaderSecWebSocketVersion::toString() {
    return createString(version);
}


}