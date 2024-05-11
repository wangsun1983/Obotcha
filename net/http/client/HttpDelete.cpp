#include "HttpDelete.hpp"
#include "HttpMethod.hpp"

namespace obotcha {

_HttpDelete::_HttpDelete(String url) {
    auto r = this->getHeader();
    HttpUrl httpurl = HttpUrl::New(url);
    r->setMethod(st(HttpMethod)::Id::Delete);
    r->setHost(HttpHeaderHost::New(httpurl->getHost(),httpurl->getPort()));
    r->setUrl(url);
}

String _HttpDelete::getMethodName() const {
    return st(HttpMethod)::ToString(st(HttpMethod)::Id::Delete);
}

}
