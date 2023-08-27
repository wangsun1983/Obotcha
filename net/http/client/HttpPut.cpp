#include "HttpPut.hpp"
#include "HttpMethod.hpp"

namespace obotcha {

_HttpPut::_HttpPut(String url):_HttpClientBaseRequest{url} {
    this->getHeader()->setMethod(st(HttpMethod)::Id::Get);
}

String _HttpPut::getMethodName() const {
    return st(HttpMethod)::toString(st(HttpMethod)::Id::Get);
}

}
