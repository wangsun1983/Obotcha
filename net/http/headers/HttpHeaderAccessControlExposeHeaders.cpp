#include "HttpHeaderAccessControlExposeHeaders.hpp"
#include "HttpHeaderContentParser.hpp"

namespace obotcha {

_HttpHeaderAccessControlExposeHeaders::_HttpHeaderAccessControlExposeHeaders() {
    headers = createArrayList<String>();
}

_HttpHeaderAccessControlExposeHeaders::_HttpHeaderAccessControlExposeHeaders(String v):_HttpHeaderAccessControlExposeHeaders() {
    import(v);
}

void _HttpHeaderAccessControlExposeHeaders::import(String v) {
    st(HttpHeaderContentParser)::import(v,[this](String directive,String parameter) {
        headers->add(directive);
    });
}

void _HttpHeaderAccessControlExposeHeaders::add(String v) {
    headers->add(v->trim());
}

ArrayList<String> _HttpHeaderAccessControlExposeHeaders::get() {
    return headers;
}

String _HttpHeaderAccessControlExposeHeaders::toString() {
    String expose = "";
    auto iterator = headers->getIterator();
    while(iterator->hasValue()) {
        expose = expose->append(iterator->getValue(),",");
        iterator->next();
    }
    return expose->subString(0,expose->size() - 1);
}

}