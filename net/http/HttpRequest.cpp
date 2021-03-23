#include "HttpRequest.hpp"
#include "UUID.hpp"

namespace obotcha {

_HttpRequest::_HttpRequest(int m,HttpUrl url):_HttpPacket() {
    mUrl = url;
    this->getHeader()->setMethod(m);
}

_HttpRequest::_HttpRequest() {
    
}

HttpUrl _HttpRequest::getUrl() {
    return mUrl;
}

String _HttpRequest::toString() {
    //TODO
    return nullptr;
}
    
}

