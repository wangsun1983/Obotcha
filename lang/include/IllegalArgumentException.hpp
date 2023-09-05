#ifndef __OBOTCHA_ILLEGAL_ARGUMENT_EXCEPTION_HPP__
#define __OBOTCHA_ILLEGAL_ARGUMENT_EXCEPTION_HPP__

#include "Exception.hpp"

namespace obotcha {

DECLARE_EXCEPTION(IllegalArgumentException) {
public:
	IllegalArgumentException() = default;
};

}

#endif
