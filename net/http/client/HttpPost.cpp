#include "HttpPost.hpp"
#include "HttpMethod.hpp"

namespace obotcha {

_HttpPost::_HttpPost(String url):_HttpClientBaseRequest{url} {

    this->getHeader()->setUrl(url);
    this->getHeader()->setMethod(st(HttpMethod)::Post);
}

String _HttpPost::getMethodName() {
    return st(HttpMethod)::toString(st(HttpMethod)::Post);
}

}
