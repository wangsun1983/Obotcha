#include "HttpAcceptRanges.hpp"
#include "Math.hpp"

namespace obotcha {

_HttpAcceptRanges::_HttpAcceptRanges() {

}

_HttpAcceptRanges::_HttpAcceptRanges(String s) {
    import(s);
}

void _HttpAcceptRanges::import(String s) {
    range = s->trim();
}

void _HttpAcceptRanges::set(String s) {
    import(s);
}

String _HttpAcceptRanges::get() {
    return range;
}

String _HttpAcceptRanges::toString() {
    return range;
}

}
