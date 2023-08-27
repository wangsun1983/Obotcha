#include "HttpHeaderAllow.hpp"
#include "HttpMethod.hpp"
#include "HttpHeaderContentParser.hpp"
#include "StringBuffer.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_HttpHeaderAllow::_HttpHeaderAllow(String v):_HttpHeaderAllow() {
    load(v);
}

void _HttpHeaderAllow::load(String s) {
    methods.clear();
    st(HttpHeaderContentParser)::load(s,
        [this](String directive,[[maybe_unused]]String parameter) {
            methods.push_back(st(HttpMethod)::toId(directive));
    });
}

void _HttpHeaderAllow::add(st(HttpMethod)::Id method) {
    methods.push_back(method);
}

ArrayList<Integer> _HttpHeaderAllow::get() {
    ArrayList<Integer> list = createArrayList<Integer>();
    for(auto method:methods) {
        list->add(createInteger(static_cast<int>(method)));
    }
    return list;
}

String _HttpHeaderAllow::toString() {
    StringBuffer method = createStringBuffer();
    for(auto item:methods) {
        method->append(st(HttpMethod)::toString(item),", ");   
    }
    return method->toString(0,method->size() - 2);
}


}
