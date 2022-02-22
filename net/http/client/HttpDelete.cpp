#include "HttpDelete.hpp"
#include "HttpMethod.hpp"

namespace obotcha {

_HttpDelete::_HttpDelete(String url):_HttpClientBaseRequest{url} {
    this->getHeader()->setMethod(st(HttpMethod)::Delete);
}

String _HttpDelete::getMethodName() {
    return st(HttpMethod)::toString(st(HttpMethod)::Delete);
}

}
