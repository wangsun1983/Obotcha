#include "HttpHeaderAllow.hpp"
#include "HttpMethod.hpp"
#include "HttpHeaderContentParser.hpp"

namespace obotcha {

_HttpHeaderAllow::_HttpHeaderAllow() {
    methods = createArrayList<Integer>();
}

_HttpHeaderAllow::_HttpHeaderAllow(String v):_HttpHeaderAllow() {
    import(v);
}

void _HttpHeaderAllow::import(String s) {
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        methods->add(createInteger(st(HttpMethod)::findId(directive)));
    });
}

void _HttpHeaderAllow::add(int method) {
    methods->add(createInteger(method));
}

ArrayList<Integer> _HttpHeaderAllow::get() {
    return methods;
}

String _HttpHeaderAllow::toString() {
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
