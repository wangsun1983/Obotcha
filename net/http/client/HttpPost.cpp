#include "HttpPost.hpp"
#include "HttpMethod.hpp"

namespace obotcha {

_HttpPost::_HttpPost(String url) {
    auto r = this->getHeader();
    HttpUrl httpurl = createHttpUrl(url);
    r->setMethod(st(HttpMethod)::Id::Post);
    r->setHost(createHttpHeaderHost(httpurl->getHost(),httpurl->getPort()));
    r->setUrl(url);
}

String _HttpPost::getMethodName() const {
    return st(HttpMethod)::toString(st(HttpMethod)::Id::Post);
}

}
