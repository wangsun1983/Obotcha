#include "HttpGet.hpp"
#include "HttpMethod.hpp"

namespace obotcha {

_HttpGet::_HttpGet(String url):_HttpClientBaseRequest{url} {
    this->getHeader()->setMethod(st(HttpMethod)::Get);
}

String _HttpGet::getMethodName() const{
    return st(HttpMethod)::toString(st(HttpMethod)::Get);
}

}
