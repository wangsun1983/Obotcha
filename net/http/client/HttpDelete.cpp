#include "HttpDelete.hpp"
#include "HttpMethod.hpp"

namespace obotcha {

_HttpDelete::_HttpDelete(String url) {
    auto r = this->getHeader();
    HttpUrl httpurl = createHttpUrl(url);
    r->setMethod(st(HttpMethod)::Id::Delete);
    r->setHost(createHttpHeaderHost(httpurl->getHost(),httpurl->getPort()));
    r->setUrl(url);
}

String _HttpDelete::getMethodName() const {
    return st(HttpMethod)::ToString(st(HttpMethod)::Id::Delete);
}

}
