#include "HttpIfRange.hpp"

namespace obotcha {

_HttpIfRange::_HttpIfRange() {
    date = nullptr;
    tag = nullptr;
}

_HttpIfRange::_HttpIfRange(String v):_HttpIfRange() {
    import(v);
}

void _HttpIfRange::import(String v) {
    printf("ifrange is %s \n",v->toChars());
    if(v->trim()->startsWith("\"")) {
        printf("it is a tag \n");
        tag = v->subString(1,v->size() -2 ); //remove \"
        printf("tag is %s \n",tag->toChars());
    } else {
        printf("it is a date \n");
        date = createHttpDate(v);
    }
}

HttpDate _HttpIfRange::getDate() {
    return date;
}

String _HttpIfRange::getTag() {
    return tag;
}

void _HttpIfRange::set(HttpDate d) {
    date = d;
}

void _HttpIfRange::set(String d) {
    tag = d;
}

String _HttpIfRange::toString() {
    if(date != nullptr) {
        return date->toString();
    } else if(tag != nullptr){
        String range = "\"";
        return range->append(tag,"\"");
    }
    return nullptr;
}


}
