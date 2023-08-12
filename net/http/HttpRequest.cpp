#include "HttpRequest.hpp"
#include "Http.hpp"

namespace obotcha {

_HttpRequest::_HttpRequest(HttpPacket p) {
    this->setType(st(Http)::PacketType::Request);
    this->setEntity(p->getEntity());
    this->setHeader(p->getHeader());
}

_HttpRequest::_HttpRequest() {
    this->setType(st(Http)::PacketType::Request);
}

}

