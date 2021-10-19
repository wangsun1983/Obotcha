#include "HttpAccessControlRequestHeaders.hpp"
#include "HttpHeaderContentParser.hpp"

namespace obotcha {

_HttpAccessControlRequestHeaders::_HttpAccessControlRequestHeaders() {
    headers = createArrayList<String>();
}

_HttpAccessControlRequestHeaders::_HttpAccessControlRequestHeaders(String v):_HttpAccessControlRequestHeaders() {
    import(v);
}

void _HttpAccessControlRequestHeaders::import(String v) {
    st(HttpHeaderContentParser)::import(v,[this](String directive,String parameter) {
        headers->add(directive);
    });
}

void _HttpAccessControlRequestHeaders::addHeaders(String v) {
    headers->add(v);
}

ArrayList<String> _HttpAccessControlRequestHeaders::getHeaders() {
    return headers;
}

String _HttpAccessControlRequestHeaders::toString() {
    String expose = "";
    auto iterator = headers->getIterator();
    while(iterator->hasValue()) {
        expose = expose->append(iterator->getValue(),", ");
        iterator->next();
    }
    return expose->subString(0,expose->size() - 2);
}

}
