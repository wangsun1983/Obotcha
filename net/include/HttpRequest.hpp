#ifndef __OBOTCHA_HTTP_REQUEST_HPP__
#define __OBOTCHA_HTTP_REQUEST_HPP__

#include "HttpPacket.hpp"
#include "HttpProtocol.hpp"

namespace obotcha {

DECLARE_CLASS(HttpRequest) IMPLEMENTS(HttpPacket) {
public:

	_HttpRequest(HttpPacket p) {
        this->setProtocol(st(HttpProtocol)::HttpRequest);
        this->setEntity(p->getEntity());
        this->setHeader(p->getHeader());
    }

	_HttpRequest():_HttpPacket(){
        this->setProtocol(st(HttpProtocol)::HttpRequest);
    }
};

}
#endif
