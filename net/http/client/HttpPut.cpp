#include "HttpPut.hpp"
#include "HttpMethod.hpp"

namespace obotcha {

_HttpPut::_HttpPut(String url):_HttpClientBaseRequest{url} {
    this->getHeader()->setMethod(st(HttpMethod)::Get);
}

String _HttpPut::getMethodName() {
    return st(HttpMethod)::toString(st(HttpMethod)::Get);
}

}
