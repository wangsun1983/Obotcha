#ifndef __OBOTCHA_NULL_POINTER_EXCEPTION_HPP__
#define __OBOTCHA_NULL_POINTER_EXCEPTION_HPP__

#include "Exception.hpp"

namespace obotcha {

DECLARE_EXCEPTION(NullPointerException) {
public:
	NullPointerException() = default;
};

}

#endif
