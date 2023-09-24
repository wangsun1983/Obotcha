#include "HttpHeaderAccessControlExposeHeaders.hpp"
#include "HttpHeaderContentParser.hpp"
#include "StringBuffer.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_HttpHeaderAccessControlExposeHeaders::_HttpHeaderAccessControlExposeHeaders(String v) {
    load(v);
}

void _HttpHeaderAccessControlExposeHeaders::load(String v) {
    headers->clear();

    st(HttpHeaderContentParser)::load(v,
        [this](String directive,[[maybe_unused]] String parameter) {
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
