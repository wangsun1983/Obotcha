#include "HttpHeaderProxyAuthorization.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"

namespace obotcha {

_HttpHeaderProxyAuthorization::_HttpHeaderProxyAuthorization() {
}

_HttpHeaderProxyAuthorization::_HttpHeaderProxyAuthorization(String s) {
    import(s);
}

void _HttpHeaderProxyAuthorization::import(String s) {
    int index = s->indexOf(" ");
    type = s->subString(0,index);
    index++;
    credentials = s->subString(index,s->size() - index);
}

String _HttpHeaderProxyAuthorization::toString() {
    return type->append(" ",credentials);
}

}
