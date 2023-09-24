#include "HttpHeaderProxyAuthorization.hpp"
#include "HttpHeaderContentParser.hpp"

namespace obotcha {

_HttpHeaderProxyAuthorization::_HttpHeaderProxyAuthorization(String s) {
    load(s);
}

void _HttpHeaderProxyAuthorization::load(String s) {
    auto index = s->indexOf(" ");
    type = s->subString(0,index);
    index++;
    credentials = s->subString(index,s->size() - index);
}

String _HttpHeaderProxyAuthorization::toString() {
    return type->append(" ",credentials);
}

}
