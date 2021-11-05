#include "HttpSecWebSocketVersion.hpp"

namespace obotcha {

_HttpSecWebSocketVersion::_HttpSecWebSocketVersion() {
    version = 13;
}

_HttpSecWebSocketVersion::_HttpSecWebSocketVersion(String s):_HttpSecWebSocketVersion() {
    import(s->trim());
}

void _HttpSecWebSocketVersion::import(String s) {
    version = s->toBasicInt();
}

int _HttpSecWebSocketVersion::get() {
    return version;
}

void _HttpSecWebSocketVersion::set(int s) {
    version = s;
}

String _HttpSecWebSocketVersion::toString() {
    return createString(version);
}


}