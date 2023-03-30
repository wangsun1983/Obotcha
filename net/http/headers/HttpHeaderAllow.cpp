#include "HttpHeaderAllow.hpp"
#include "HttpMethod.hpp"
#include "HttpHeaderContentParser.hpp"
#include "StringBuffer.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_HttpHeaderAllow::_HttpHeaderAllow() {
    methods = createArrayList<Integer>();
}

_HttpHeaderAllow::_HttpHeaderAllow(String v):_HttpHeaderAllow() {
    import(v);
}

void _HttpHeaderAllow::import(String s) {
    methods->clear();
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
    ForEveryOne(item,methods) {
        method->append(st(HttpMethod)::toString(item->toValue()),", ");   
    }
    return method->toString(0,method->size() - 2);
}


}
