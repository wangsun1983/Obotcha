#ifndef __OBOTCHA_INITIALIZE_EXCEPTION_HPP__
#define __OBOTCHA_INITIALIZE_EXCEPTION_HPP__

#include "Exception.hpp"

namespace obotcha {

DECLARE_EXCEPTION(InitializeException) {
public:
	InitializeException() = default;
};

}

#endif
