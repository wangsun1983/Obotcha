#include "HttpHeaderAllow.hpp"
#include "HttpMethod.hpp"
#include "HttpHeaderContentParser.hpp"
#include "StringBuffer.hpp"

namespace obotcha {

_HttpHeaderAllow::_HttpHeaderAllow() {
    methods = createArrayList<Integer>();
}

_HttpHeaderAllow::_HttpHeaderAllow(String v):_HttpHeaderAllow() {
    import(v);
}

void _HttpHeaderAllow::import(String s) {
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        methods->add(createInteger(st(HttpMethod)::toId(directive)));
    });
}

void _HttpHeaderAllow::add(int method) {
    methods->add(createInteger(method));
}

ArrayList<Integer> _HttpHeaderAllow::get() {
    return methods;
}

String _HttpHeaderAllow::toString() {
    StringBuffer method = createStringBuffer();
    auto iterator = methods->getIterator();
    while(iterator->hasValue()) {
        Integer v = iterator->getValue();
        method->append(st(HttpMethod)::toString(v->toValue()),", ");   
        iterator->next();
    }

    return method->toString(0,method->size() - 2);
}


}
