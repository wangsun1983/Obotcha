#include "HttpHeaderIfRange.hpp"

namespace obotcha {

_HttpHeaderIfRange::_HttpHeaderIfRange(String v) {
    load(v);
}

void _HttpHeaderIfRange::load(String v) {
    if(v->trim()->startsWith("\"")) {
        tag = v->subString(1,v->size() -2 ); //remove \"
    } else {
        date = HttpDate::New(v);
    }
}

HttpDate _HttpHeaderIfRange::getDate() const {
    return date;
}

String _HttpHeaderIfRange::getTag() const {
    return tag;
}

void _HttpHeaderIfRange::set(HttpDate d) {
    date = d;
}

void _HttpHeaderIfRange::set(String d) {
    tag = d;
}

String _HttpHeaderIfRange::toString() {
    if(date != nullptr) {
        return date->toString();
    } else if(tag != nullptr){
        String range = "\"";
        return range->append(tag,"\"");
    }
    return nullptr;
}

}
