#include "HttpHeaderAcceptRanges.hpp"
#include "Math.hpp"

namespace obotcha {

_HttpHeaderAcceptRanges::_HttpHeaderAcceptRanges(String s) {
    load(s);
}

void _HttpHeaderAcceptRanges::load(String s) {
    range = s->trim();
}

void _HttpHeaderAcceptRanges::set(String s) {
    load(s);
}

String _HttpHeaderAcceptRanges::get() {
    return range;
}

String _HttpHeaderAcceptRanges::toString() {
    return range;
}

}
