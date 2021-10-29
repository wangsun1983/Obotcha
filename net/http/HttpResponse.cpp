#include "HttpResponse.hpp"

namespace obotcha {

_HttpResponse::_HttpResponse(HttpPacket p) {
    this->setType(st(HttpPacket)::Response);
    this->setEntity(p->getEntity());
    this->setHeader(p->getHeader());
}

_HttpResponse::_HttpResponse() {
    this->setType(st(HttpPacket)::Response);
}

}

