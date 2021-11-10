#include "HttpHeaderAccessControlRequestHeaders.hpp"
#include "HttpHeaderContentParser.hpp"

namespace obotcha {

_HttpHeaderAccessControlRequestHeaders::_HttpHeaderAccessControlRequestHeaders() {
    headers = createArrayList<String>();
}

_HttpHeaderAccessControlRequestHeaders::_HttpHeaderAccessControlRequestHeaders(String v):_HttpHeaderAccessControlRequestHeaders() {
    import(v);
}

void _HttpHeaderAccessControlRequestHeaders::import(String v) {
    st(HttpHeaderContentParser)::import(v,[this](String directive,String parameter) {
        headers->add(directive);
    });
}

void _HttpHeaderAccessControlRequestHeaders::add(String v) {
    headers->add(v->trim());
}

ArrayList<String> _HttpHeaderAccessControlRequestHeaders::get() {
    return headers;
}

String _HttpHeaderAccessControlRequestHeaders::toString() {
    String expose = "";
    auto iterator = headers->getIterator();
    while(iterator->hasValue()) {
        expose = expose->append(iterator->getValue(),", ");
        iterator->next();
    }
    return expose->subString(0,expose->size() - 2);
}

}
