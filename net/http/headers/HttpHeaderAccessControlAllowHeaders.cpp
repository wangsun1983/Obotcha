#include "HttpHeaderAccessControlAllowHeaders.hpp"
#include "HttpHeaderContentParser.hpp"

namespace obotcha {

_HttpHeaderAccessControlAllowHeaders::_HttpHeaderAccessControlAllowHeaders() {
    allowedHeaders = createArrayList<String>();
}

_HttpHeaderAccessControlAllowHeaders::_HttpHeaderAccessControlAllowHeaders(String v):_HttpHeaderAccessControlAllowHeaders() {
    import(v);
}

void _HttpHeaderAccessControlAllowHeaders::import(String s) {
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        allowedHeaders->add(directive);
    });
}

ArrayList<String> _HttpHeaderAccessControlAllowHeaders::get() {
    return allowedHeaders;
}

void _HttpHeaderAccessControlAllowHeaders::add(String v) {
    allowedHeaders->add(v);
}

String _HttpHeaderAccessControlAllowHeaders::toString() {
    String allow = "";
    auto iterator = allowedHeaders->getIterator();
    while(iterator->hasValue()) {
        allow = allow->append(iterator->getValue(),", ");
        iterator->next();
    }

    return allow->subString(0,allow->size() - 2);
}


}