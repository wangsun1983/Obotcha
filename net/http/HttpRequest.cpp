#include "HttpRequest.hpp"
#include "UUID.hpp"

namespace obotcha {

_HttpRequest::_HttpRequest(int m,HttpUrl url):_HttpPacket() {
    this->getHeader()->setMethod(m);
}

_HttpRequest::_HttpRequest() {
    
}

String _HttpRequest::toString() {
    //TODO
    return nullptr;
}
    
}

