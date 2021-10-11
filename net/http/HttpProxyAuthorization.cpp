#include "HttpProxyAuthorization.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"

namespace obotcha {

_HttpProxyAuthorization::_HttpProxyAuthorization() {
}

_HttpProxyAuthorization::_HttpProxyAuthorization(String s) {
    import(s);
}

void _HttpProxyAuthorization::import(String s) {
    int index = s->indexOf(" ");
    type = s->subString(0,index);
    credentials = s->subString(++index,s->size() - index);
}

String _HttpProxyAuthorization::toString() {
    return type->append(" ",credentials);
}

}
