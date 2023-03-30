#include "HttpHeaderAccessControlAllowMethods.hpp"
#include "HttpMethod.hpp"
#include "HttpHeaderContentParser.hpp"
#include "StringBuffer.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_HttpHeaderAccessControlAllowMethods::_HttpHeaderAccessControlAllowMethods() {
    methods = createArrayList<Integer>();
}

_HttpHeaderAccessControlAllowMethods::_HttpHeaderAccessControlAllowMethods(String v):_HttpHeaderAccessControlAllowMethods() {
    import(v);
}

void _HttpHeaderAccessControlAllowMethods::import(String s) {
    methods->clear();
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        methods->add(createInteger(st(HttpMethod)::toId(directive)));
    });
}

void _HttpHeaderAccessControlAllowMethods::add(int method) {
    methods->add(createInteger(method));
}

ArrayList<Integer> _HttpHeaderAccessControlAllowMethods::get() {
    return methods;
}

String _HttpHeaderAccessControlAllowMethods::toString() {
    StringBuffer method = createStringBuffer();
    ForEveryOne(item,methods) {
            method->append(st(HttpMethod)::toString(item->toValue()),", ");
    }

    return method->toString(0,method->size() - 2);
}


}
