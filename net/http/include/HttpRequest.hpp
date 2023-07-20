#ifndef __OBOTCHA_HTTP_REQUEST_HPP__
#define __OBOTCHA_HTTP_REQUEST_HPP__

#include "HttpPacket.hpp"

namespace obotcha {

DECLARE_CLASS(HttpRequest) IMPLEMENTS(HttpPacket) {
public:
	explicit _HttpRequest(HttpPacket p);
	_HttpRequest();
};

}
#endif
