#ifndef __OBOTCHA_OUT_OF_MEMORY_EXCEPTION_HPP__
#define __OBOTCHA_OUT_OF_MEMORY_EXCEPTION_HPP__

#include "Exception.hpp"

namespace obotcha {

DECLARE_EXCEPTION(OutOfMemoryException){
public:
	OutOfMemoryException() = default;
};

}

#endif
