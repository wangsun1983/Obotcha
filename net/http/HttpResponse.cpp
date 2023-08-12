#include "HttpResponse.hpp"
#include "Http.hpp"
namespace obotcha {

_HttpResponse::_HttpResponse(HttpPacket p) {
    this->setType(st(Http)::PacketType::Response);
    this->setEntity(p->getEntity());
    this->setHeader(p->getHeader());
}

_HttpResponse::_HttpResponse() {
    this->setType(st(Http)::PacketType::Response);
}

}

