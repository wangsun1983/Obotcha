#ifndef __OBOTCHA_METHOD_NOT_SUPPORT_EXCEPTION_HPP__
#define __OBOTCHA_METHOD_NOT_SUPPORT_EXCEPTION_HPP__

#include "Exception.hpp"

namespace obotcha {

DECLARE_EXCEPTION(MethodNotSupportException) {
public:
	MethodNotSupportException() = default;
};

}

#endif
