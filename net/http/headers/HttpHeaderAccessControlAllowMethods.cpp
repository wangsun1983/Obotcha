#include "HttpHeaderAccessControlAllowMethods.hpp"
#include "HttpMethod.hpp"
#include "HttpHeaderContentParser.hpp"

namespace obotcha {

_HttpHeaderAccessControlAllowMethods::_HttpHeaderAccessControlAllowMethods() {
    methods = createArrayList<Integer>();
}

_HttpHeaderAccessControlAllowMethods::_HttpHeaderAccessControlAllowMethods(String v):_HttpHeaderAccessControlAllowMethods() {
    import(v);
}

void _HttpHeaderAccessControlAllowMethods::import(String s) {
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        methods->add(createInteger(st(HttpMethod)::findId(directive)));
    });
}

void _HttpHeaderAccessControlAllowMethods::add(int method) {
    methods->add(createInteger(method));
}

ArrayList<Integer> _HttpHeaderAccessControlAllowMethods::get() {
    return methods;
}

String _HttpHeaderAccessControlAllowMethods::toString() {
    String method = "";
    auto iterator = methods->getIterator();
    while(iterator->hasValue()) {
        Integer v = iterator->getValue();
        method = method->append(st(HttpMethod)::findString(v->toValue()),", ");
        iterator->next();
    }

    return method->subString(0,method->size() - 2);
}


}
