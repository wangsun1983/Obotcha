#include "HttpHeaderRetryAfter.hpp"
#include "HttpHeaderContentParser.hpp"

namespace obotcha {

_HttpHeaderRetryAfter::_HttpHeaderRetryAfter(String s) {
    load(s);
}

void _HttpHeaderRetryAfter::load(String value) {
    if(value->containsIgnoreCase("GMT")) {
        date = HttpDate::New(value);
    } else {
        delay = value->toBasicInt();
    }
}

HttpDate _HttpHeaderRetryAfter::getDate() const {
    return date;
}

int _HttpHeaderRetryAfter::getDelayInterval() const {
    return delay;
}

void _HttpHeaderRetryAfter::setDate(HttpDate d) {
    date = d;
}

void _HttpHeaderRetryAfter::setDelayInterval(int v) {
    delay = v;
}

String _HttpHeaderRetryAfter::toString() {
    return (date != nullptr)?date->toString():String::New(delay);
}


}
