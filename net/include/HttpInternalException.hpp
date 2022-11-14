#ifndef __OBOTCHA_HTTP_INTERNAL_EXCEPTION_HPP__
#define __OBOTCHA_HTTP_INTERNAL_EXCEPTION_HPP__

#include "Exception.hpp"

namespace obotcha {

DECLARE_EXCEPTION(HttpInternalException) {
public:
	HttpInternalException() {}
};

}

#endif
