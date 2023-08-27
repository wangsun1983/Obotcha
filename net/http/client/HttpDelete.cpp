#include "HttpDelete.hpp"
#include "HttpMethod.hpp"

namespace obotcha {

_HttpDelete::_HttpDelete(String url):_HttpClientBaseRequest{url} {
    this->getHeader()->setMethod(st(HttpMethod)::Id::Delete);
}

String _HttpDelete::getMethodName() const {
    return st(HttpMethod)::toString(st(HttpMethod)::Id::Delete);
}

}
