#include "HttpAccessControlAllowMethods.hpp"
#include "HttpMethod.hpp"
#include "HttpHeaderContentParser.hpp"

namespace obotcha {

_HttpAccessControlAllowMethods::_HttpAccessControlAllowMethods() {
    methods = createArrayList<Integer>();
}

_HttpAccessControlAllowMethods::_HttpAccessControlAllowMethods(String v):_HttpAccessControlAllowMethods() {
    import(v);
}

void _HttpAccessControlAllowMethods::import(String s) {
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        methods->add(createInteger(st(HttpMethod)::toInt(directive)));
    });
}

void _HttpAccessControlAllowMethods::addMethod(int method) {
    methods->add(createInteger(method));
}

ArrayList<Integer> _HttpAccessControlAllowMethods::getMethods() {
    return methods;
}

String _HttpAccessControlAllowMethods::toString() {

}


}
