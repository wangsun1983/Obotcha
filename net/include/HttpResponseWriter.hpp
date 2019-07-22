#ifndef __HTTP_RESPONSE_WRITER_HPP__
#define __HTTP_RESPONSE_WRITER_HPP__

#include "HttpResponse.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpResponseWriter) {
public:
    _HttpResponseWriter(int fd);
	int write(HttpResponse);

private:
    int mFd;
};

}

#endif
