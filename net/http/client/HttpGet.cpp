#include "HttpGet.hpp"
#include "HttpMethod.hpp"

namespace obotcha {

_HttpGet::_HttpGet(String url) {
    auto r = this->getHeader();
    HttpUrl httpurl = createHttpUrl(url);
    r->setMethod(st(HttpMethod)::Id::Get);
    r->setHost(createHttpHeaderHost(httpurl->getHost(),httpurl->getPort()));
    r->setUrl(url);
}

String _HttpGet::getMethodName() const{
    return st(HttpMethod)::toString(st(HttpMethod)::Id::Get);
}

}
