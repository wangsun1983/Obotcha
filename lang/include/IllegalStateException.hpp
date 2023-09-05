#ifndef __OBOTCHA_ILLEGAL_STATE_EXCEPTION_HPP__
#define __OBOTCHA_ILLEGAL_STATE_EXCEPTION_HPP__

#include "Exception.hpp"

namespace obotcha {

DECLARE_EXCEPTION(IllegalStateException) {
public:
	IllegalStateException() = default;
};

}

#endif
