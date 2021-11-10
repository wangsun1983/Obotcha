#include "HttpHeaderAcceptRanges.hpp"
#include "Math.hpp"

namespace obotcha {

_HttpHeaderAcceptRanges::_HttpHeaderAcceptRanges() {

}

_HttpHeaderAcceptRanges::_HttpHeaderAcceptRanges(String s) {
    import(s);
}

void _HttpHeaderAcceptRanges::import(String s) {
    range = s->trim();
}

void _HttpHeaderAcceptRanges::set(String s) {
    import(s);
}

String _HttpHeaderAcceptRanges::get() {
    return range;
}

String _HttpHeaderAcceptRanges::toString() {
    return range;
}

}
