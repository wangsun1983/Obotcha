#include "HttpPut.hpp"
#include "HttpMethod.hpp"

namespace obotcha {

_HttpPut::_HttpPut(String url) {
    auto r = this->getHeader();
    HttpUrl httpurl = createHttpUrl(url);
    r->setMethod(st(HttpMethod)::Id::Put);
    r->setHost(createHttpHeaderHost(httpurl->getHost(),httpurl->getPort()));
    r->setUrl(url);
}

String _HttpPut::getMethodName() const {
    return st(HttpMethod)::ToString(st(HttpMethod)::Id::Put);
}

}
