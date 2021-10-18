#include "HttpAccessControlRequestHeaders.hpp"
#include "HttpHeaderContentParser.hpp"

namespace obotcha {

_HttpAccessCrontrolRequestHeaders::_HttpAccessCrontrolRequestHeaders() {
    headers = createArrayList<String>();
}

_HttpAccessCrontrolRequestHeaders::_HttpAccessCrontrolRequestHeaders(String v):_HttpAccessCrontrolRequestHeaders() {
    import(v);
}

void _HttpAccessCrontrolRequestHeaders::import(String v) {
    st(HttpHeaderContentParser)::import(v,[this](String directive,String parameter) {
        headers->add(directive);
    });
}

void _HttpAccessCrontrolRequestHeaders::addHeaders(String v) {
    headers->add(v);
}

ArrayList<String> _HttpAccessCrontrolRequestHeaders::getHeaders() {
    return headers;
}

String _HttpAccessCrontrolRequestHeaders::toString() {
    String expose = "";
    auto iterator = headers->getIterator();
    while(iterator->hasValue()) {
        expose = expose->append(iterator->getValue(),",");
        iterator->next();
    }
    return expose->subString(0,expose->size() - 1);
}

}
