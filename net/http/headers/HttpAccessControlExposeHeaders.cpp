#include "HttpAccessControlExposeHeaders.hpp"
#include "HttpHeaderContentParser.hpp"

namespace obotcha {

_HttpAccessControlExposeHeaders::_HttpAccessControlExposeHeaders() {
    headers = createArrayList<String>();
}

_HttpAccessControlExposeHeaders::_HttpAccessControlExposeHeaders(String v):_HttpAccessControlExposeHeaders() {
    import(v);
}

void _HttpAccessControlExposeHeaders::import(String v) {
    st(HttpHeaderContentParser)::import(v,[this](String directive,String parameter) {
        headers->add(directive);
    });
}

void _HttpAccessControlExposeHeaders::add(String v) {
    headers->add(v->trim());
}

ArrayList<String> _HttpAccessControlExposeHeaders::get() {
    return headers;
}

String _HttpAccessControlExposeHeaders::toString() {
    String expose = "";
    auto iterator = headers->getIterator();
    while(iterator->hasValue()) {
        expose = expose->append(iterator->getValue(),",");
        iterator->next();
    }
    return expose->subString(0,expose->size() - 1);
}

}
