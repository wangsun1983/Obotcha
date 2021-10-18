#include "HttpAccessControlAllowHeaders.hpp"
#include "HttpHeaderContentParser.hpp"

namespace obotcha {

_HttpAccessControlAllowHeaders::_HttpAccessControlAllowHeaders() {
    allowedHeaders = createArrayList<String>();
}

_HttpAccessControlAllowHeaders::_HttpAccessControlAllowHeaders(String v):_HttpAccessControlAllowHeaders() {
    import(v);
}

void _HttpAccessControlAllowHeaders::import(String s) {
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        allowedHeaders->add(directive);
    });
}

ArrayList<String> _HttpAccessControlAllowHeaders::getAllowedHeaders() {
    return allowedHeaders;
}

void _HttpAccessControlAllowHeaders::addHeader(String v) {
    allowedHeaders->add(v);
}

String _HttpAccessControlAllowHeaders::toString() {
    String allow = "";
    auto iterator = allowedHeaders->getIterator();
    while(iterator->hasValue()) {
        allow = allow->append(iterator->getValue(),",");
        iterator->next();
    }

    return allow->subString(0,allow->size() - 1);
}


}
