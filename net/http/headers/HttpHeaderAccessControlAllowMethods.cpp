#include "HttpHeaderAccessControlAllowMethods.hpp"
#include "HttpMethod.hpp"
#include "HttpHeaderContentParser.hpp"
#include "StringBuffer.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_HttpHeaderAccessControlAllowMethods::_HttpHeaderAccessControlAllowMethods(String v) {
    load(v);
}

void _HttpHeaderAccessControlAllowMethods::load(String s) {
    methods.clear();
    st(HttpHeaderContentParser)::load(s,
        [this](String directive,[[maybe_unused]]String parameter) {
            methods.push_back(st(HttpMethod)::ToId(directive));
    });
}

void _HttpHeaderAccessControlAllowMethods::add(st(HttpMethod)::Id method) {
    methods.push_back(method);
}

List<st(HttpMethod)::Id> _HttpHeaderAccessControlAllowMethods::get() const {
    List<st(HttpMethod)::Id> result = createList<st(HttpMethod)::Id>(methods.size());
    size_t index = 0;
    for(auto m:methods) {
        result[index] = m;
        index++;
    }

    return result;
}

String _HttpHeaderAccessControlAllowMethods::toString() {
    StringBuffer method = createStringBuffer();
    for(auto item:methods) {
            method->append(st(HttpMethod)::ToString(item),", ");
    }

    return method->toString(0,method->size() - 2);
}


}
