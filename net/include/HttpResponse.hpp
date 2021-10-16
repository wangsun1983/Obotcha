#ifndef __OBOTCHA_HTTP_RESPONSE_HPP__
#define __OBOTCHA_HTTP_RESPONSE_HPP__

#include "HttpPacket.hpp"
#include "HttpProtocol.hpp"

namespace obotcha {

DECLARE_CLASS(HttpResponse) IMPLEMENTS(HttpPacket) {
public:
    using _HttpPacket::_HttpPacket;

    _HttpResponse(HttpPacket p) {
        this->setProtocol(st(HttpProtocol)::HttpResponse);
        this->setEntity(p->getEntity());
        this->setProtocol(p->getProtocol());
        this->setEntity(p->getEntity());
    }

	_HttpResponse():_HttpPacket(){
        this->setProtocol(st(HttpProtocol)::HttpResponse);
    }
};

}
#endif
