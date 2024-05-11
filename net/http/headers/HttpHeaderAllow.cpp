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
            methods.push_back(st(HttpMethod)::ToId(directive));
    });
}

void _HttpHeaderAllow::add(st(HttpMethod)::Id method) {
    methods.push_back(method);
}

List<st(HttpMethod)::Id> _HttpHeaderAllow::get() const {
    List<st(HttpMethod)::Id> list = List<st(HttpMethod)::Id>::New(methods.size());
    size_t index = 0;
    for(auto method:methods) {
        list[index] = method;
        index++;
    }
    return list;
}

String _HttpHeaderAllow::toString() {
    StringBuffer method = StringBuffer::New();
    for(auto item:methods) {
        method->append(st(HttpMethod)::ToString(item),", ");   
    }
    return method->toString(0,method->size() - 2);
}


}
