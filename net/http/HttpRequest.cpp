#include "HttpRequest.hpp"

namespace obotcha {

_HttpRequest::_HttpRequest(HttpPacket p) {
    this->setType(st(HttpPacket)::Request);
    this->setEntity(p->getEntity());
    this->setHeader(p->getHeader());
}

_HttpRequest::_HttpRequest() {
    this->setType(st(HttpPacket)::Request);
}

}

