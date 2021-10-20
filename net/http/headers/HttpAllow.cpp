#include "HttpAllow.hpp"
#include "HttpMethod.hpp"
#include "HttpHeaderContentParser.hpp"

namespace obotcha {

_HttpAllow::_HttpAllow() {
    methods = createArrayList<Integer>();
}

_HttpAllow::_HttpAllow(String v):_HttpAllow() {
    import(v);
}

void _HttpAllow::import(String s) {
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        methods->add(createInteger(st(HttpMethod)::toInt(directive)));
    });
}

void _HttpAllow::add(int method) {
    methods->add(createInteger(method));
}

ArrayList<Integer> _HttpAllow::get() {
    return methods;
}

String _HttpAllow::toString() {
    String method = "";
    auto iterator = methods->getIterator();
    while(iterator->hasValue()) {
        Integer v = iterator->getValue();
        method = method->append(st(HttpMethod)::toString(v->toValue()),", ");   
        iterator->next();
    }

    return method->subString(0,method->size() - 2);
}


}
