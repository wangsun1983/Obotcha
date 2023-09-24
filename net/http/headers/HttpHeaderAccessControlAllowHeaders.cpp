#include "HttpHeaderAccessControlAllowHeaders.hpp"
#include "HttpHeaderContentParser.hpp"
#include "StringBuffer.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_HttpHeaderAccessControlAllowHeaders::_HttpHeaderAccessControlAllowHeaders(String v) {
    load(v);
}

void _HttpHeaderAccessControlAllowHeaders::load(String s) {
    allowedHeaders->clear();
    st(HttpHeaderContentParser)::load(s,
        [this](String directive,[[maybe_unused]]String parameter) {
            allowedHeaders->add(directive);
    });
}

ArrayList<String> _HttpHeaderAccessControlAllowHeaders::get() {
    return allowedHeaders;
}

void _HttpHeaderAccessControlAllowHeaders::add(String v) {
    allowedHeaders->add(v);
}

String _HttpHeaderAccessControlAllowHeaders::toString() {
    StringBuffer allow = createStringBuffer();
    ForEveryOne(item,allowedHeaders) {
        allow->append(item,", ");
    }
    return allow->toString(0,allow->size() - 2);
}


}
