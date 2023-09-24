#include "HttpHeaderAllow.hpp"
#include "HttpHeaderContentParser.hpp"
#include "StringBuffer.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_HttpHeaderAllow::_HttpHeaderAllow(String v) {
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

List<st(HttpMethod)::Id> _HttpHeaderAllow::get() const {
    List<st(HttpMethod)::Id> list = createList<st(HttpMethod)::Id>(methods.size());
    size_t index = 0;
    for(auto method:methods) {
        list[index] = method;
        index++;
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
