#include "HttpAccessControlExposeHeaders.hpp"
#include "HttpHeaderContentParser.hpp"

namespace obotcha {

_HttpAccessCrontrolExposeHeaders::_HttpAccessCrontrolExposeHeaders() {
    headers = createArrayList<String>();
}

_HttpAccessCrontrolExposeHeaders::_HttpAccessCrontrolExposeHeaders(String v):_HttpAccessCrontrolExposeHeaders() {
    import(v);
}

void _HttpAccessCrontrolExposeHeaders::import(String v) {
    st(HttpHeaderContentParser)::import(v,[this](String directive,String parameter) {
        headers->add(directive);
    });
}

void _HttpAccessCrontrolExposeHeaders::addHeaders(String v) {
    headers->add(v);
}

ArrayList<String> _HttpAccessCrontrolExposeHeaders::getHeaders() {
    return headers;
}

String _HttpAccessCrontrolExposeHeaders::toString() {
    String expose = "";
    auto iterator = headers->getIterator();
    while(iterator->hasValue()) {
        expose = expose->append(iterator->getValue(),",");
        iterator->next();
    }
    return expose->subString(0,expose->size() - 1);
}

}
