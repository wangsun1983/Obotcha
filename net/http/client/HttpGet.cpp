#include "HttpGet.hpp"
#include "HttpMethod.hpp"

namespace obotcha {

_HttpGet::_HttpGet(String url) {
    auto r = this->getHeader();
    HttpUrl httpurl = HttpUrl::New(url);
    r->setMethod(st(HttpMethod)::Id::Get);
    r->setHost(HttpHeaderHost::New(httpurl->getHost(),httpurl->getPort()));
    r->setUrl(url);
}

String _HttpGet::getMethodName() const{
    return st(HttpMethod)::ToString(st(HttpMethod)::Id::Get);
}

}
