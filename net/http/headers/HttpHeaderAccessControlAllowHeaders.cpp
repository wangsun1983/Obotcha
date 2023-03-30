#include "HttpHeaderAccessControlAllowHeaders.hpp"
#include "HttpHeaderContentParser.hpp"
#include "StringBuffer.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_HttpHeaderAccessControlAllowHeaders::_HttpHeaderAccessControlAllowHeaders() {
    allowedHeaders = createArrayList<String>();
}

_HttpHeaderAccessControlAllowHeaders::_HttpHeaderAccessControlAllowHeaders(String v):_HttpHeaderAccessControlAllowHeaders() {
    import(v);
}

void _HttpHeaderAccessControlAllowHeaders::import(String s) {
    allowedHeaders->clear();
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
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
