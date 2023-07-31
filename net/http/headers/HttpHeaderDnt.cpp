#include "HttpHeaderDnt.hpp"

namespace obotcha {

_HttpHeaderDnt::_HttpHeaderDnt(String s) {
    load(s);
}

void _HttpHeaderDnt::load(String s) {
    dnt = s->toBasicInt();
}

void _HttpHeaderDnt::set(int s) {
    dnt = s;
}

int _HttpHeaderDnt::get() const {
    return dnt;
}

String _HttpHeaderDnt::toString() {
    return (dnt >= 0)?createString(dnt):nullptr;
}

}
