#include "HttpHeaderAccessControlExposeHeaders.hpp"
#include "HttpHeaderContentParser.hpp"
#include "StringBuffer.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_HttpHeaderAccessControlExposeHeaders::_HttpHeaderAccessControlExposeHeaders() {
    headers = createArrayList<String>();
}

_HttpHeaderAccessControlExposeHeaders::_HttpHeaderAccessControlExposeHeaders(String v):_HttpHeaderAccessControlExposeHeaders() {
    import(v);
}

void _HttpHeaderAccessControlExposeHeaders::import(String v) {
    headers->clear();

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
    StringBuffer expose = createStringBuffer();
    ForEveryOne(item,headers) {
        expose->append(item,",");
    }

    return expose->toString(0,expose->size() - 1);
}

}
