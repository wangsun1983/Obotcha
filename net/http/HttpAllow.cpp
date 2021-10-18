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

void _HttpAllow::addMethod(int method) {
    methods->add(createInteger(method));
}

ArrayList<Integer> _HttpAllow::getMethods() {
    return methods;
}

String _HttpAllow::toString() {

}


}
