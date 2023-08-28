#include "HttpHeaderAccessControlAllowMethods.hpp"
#include "HttpMethod.hpp"
#include "HttpHeaderContentParser.hpp"
#include "StringBuffer.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_HttpHeaderAccessControlAllowMethods::_HttpHeaderAccessControlAllowMethods(String v):_HttpHeaderAccessControlAllowMethods() {
    load(v);
}

void _HttpHeaderAccessControlAllowMethods::load(String s) {
    methods.clear();
    st(HttpHeaderContentParser)::load(s,
        [this](String directive,[[maybe_unused]]String parameter) {
            methods.push_back(st(HttpMethod)::toId(directive));
    });
}

void _HttpHeaderAccessControlAllowMethods::add(st(HttpMethod)::Id method) {
    methods.push_back(method);
}

ArrayList<Integer> _HttpHeaderAccessControlAllowMethods::get() const {
    ArrayList<Integer> result = createArrayList<Integer>();
    for(auto m:methods) {
        result->add(createInteger(static_cast<int>(m)));
    }

    return result;
}

String _HttpHeaderAccessControlAllowMethods::toString() {
    StringBuffer method = createStringBuffer();
    for(auto item:methods) {
            method->append(st(HttpMethod)::toString(item),", ");
    }

    return method->toString(0,method->size() - 2);
}


}
