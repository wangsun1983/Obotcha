#include "HttpPost.hpp"
#include "HttpMethod.hpp"

namespace obotcha {

_HttpPost::_HttpPost(String url) {
    auto r = this->getHeader();
    HttpUrl httpurl = HttpUrl::New(url);
    r->setMethod(st(HttpMethod)::Id::Post);
    r->setHost(HttpHeaderHost::New(httpurl->getHost(),httpurl->getPort()));
    r->setUrl(url);
}

String _HttpPost::getMethodName() const {
    return st(HttpMethod)::ToString(st(HttpMethod)::Id::Post);
}

}
