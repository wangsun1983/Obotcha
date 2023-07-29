#include "HttpHeaderAccessControlRequestHeaders.hpp"
#include "HttpHeaderContentParser.hpp"
#include "StringBuffer.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_HttpHeaderAccessControlRequestHeaders::_HttpHeaderAccessControlRequestHeaders() {
    headers = createArrayList<String>();
}

_HttpHeaderAccessControlRequestHeaders::_HttpHeaderAccessControlRequestHeaders(String v):_HttpHeaderAccessControlRequestHeaders() {
    load(v);
}

void _HttpHeaderAccessControlRequestHeaders::load(String v) {
    headers->clear();
    
    st(HttpHeaderContentParser)::load(v,
        [this](String directive,[[maybe_unused]]String parameter) {
            headers->add(directive);
    });
}

void _HttpHeaderAccessControlRequestHeaders::add(String v) {
    headers->add(v->trim());
}

ArrayList<String> _HttpHeaderAccessControlRequestHeaders::get() const {
    return headers;
}

String _HttpHeaderAccessControlRequestHeaders::toString() {
    StringBuffer expose = createStringBuffer();
    ForEveryOne(item,headers) {
        expose->append(item,", ");
    }
    return expose->toString(0,expose->size() - 2);
}

}
