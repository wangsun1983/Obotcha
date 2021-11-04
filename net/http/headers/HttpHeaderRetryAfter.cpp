#include "HttpHeaderRetryAfter.hpp"
#include "HttpHeaderContentParser.hpp"

namespace obotcha {

_HttpHeaderRetryAfter::_HttpHeaderRetryAfter() {
    date = nullptr;
    delay = -1;
}

_HttpHeaderRetryAfter::_HttpHeaderRetryAfter(String s):_HttpHeaderRetryAfter() {
    import(s);
}

void _HttpHeaderRetryAfter::import(String value) {
    if(value->containsIgnoreCase("GMT")) {
        date = createHttpDate(value);
    } else {
        delay = value->toBasicInt();
    }
}

HttpDate _HttpHeaderRetryAfter::getDate() {
    return date;
}

int _HttpHeaderRetryAfter::getDelayInterval() {
    return delay;
}

void _HttpHeaderRetryAfter::setDate(HttpDate d) {
    date = d;
}

void _HttpHeaderRetryAfter::setDelayInterval(int v) {
    delay = v;
}

String _HttpHeaderRetryAfter::toString() {
    if(date != nullptr) {
        return date->toString();
    } else {
        return createString(delay);
    }
}


}
