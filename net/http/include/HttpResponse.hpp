#ifndef __OBOTCHA_HTTP_RESPONSE_HPP__
#define __OBOTCHA_HTTP_RESPONSE_HPP__

#include "HttpPacket.hpp"

namespace obotcha {

DECLARE_CLASS(HttpResponse) IMPLEMENTS(HttpPacket) {
public:
    //using _HttpPacket::_HttpPacket;
    explicit _HttpResponse(HttpPacket p);
	_HttpResponse();
};

}
#endif
