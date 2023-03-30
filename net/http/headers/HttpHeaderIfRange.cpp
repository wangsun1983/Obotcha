#include "HttpHeaderIfRange.hpp"

namespace obotcha {

_HttpHeaderIfRange::_HttpHeaderIfRange() {
    date = nullptr;
    tag = nullptr;
}

_HttpHeaderIfRange::_HttpHeaderIfRange(String v):_HttpHeaderIfRange() {
    import(v);
}

void _HttpHeaderIfRange::import(String v) {
    if(v->trim()->startsWith("\"")) {
        tag = v->subString(1,v->size() -2 ); //remove \"
    } else {
        date = createHttpDate(v);
    }
}

HttpDate _HttpHeaderIfRange::getDate() {
    return date;
}

String _HttpHeaderIfRange::getTag() {
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
