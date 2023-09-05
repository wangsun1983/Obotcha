#ifndef __OBOTCHA_TIME_OUT_EXCEPTION_HPP__
#define __OBOTCHA_TIME_OUT_EXCEPTION_HPP__

#include "Exception.hpp"

namespace obotcha {

DECLARE_EXCEPTION(TimeOutException) {
public:
	TimeOutException() = default;
};

}

#endif
