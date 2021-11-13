#include "HttpHeaderSourceMap.hpp"

namespace obotcha {

_HttpHeaderSourceMap::_HttpHeaderSourceMap() {

}

_HttpHeaderSourceMap::_HttpHeaderSourceMap(String s) {
    import(s);
}

void _HttpHeaderSourceMap::import(String s) {
    url = s->trim();
}

void _HttpHeaderSourceMap::set(String s) {
    url = s->trim();
}

String _HttpHeaderSourceMap::get() {
    return url;
}

String _HttpHeaderSourceMap::toString() {
    return url;
}

}
