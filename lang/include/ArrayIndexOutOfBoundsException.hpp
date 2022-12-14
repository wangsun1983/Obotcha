#ifndef __OBOTCHA_ARRAY_INDEX_OUTOF_BOUNDS_EXCEPTION_HPP__
#define __OBOTCHA_ARRAY_INDEX_OUTOF_BOUNDS_EXCEPTION_HPP__

#include "Exception.hpp"

namespace obotcha {

DECLARE_EXCEPTION(ArrayIndexOutOfBoundsException){
public:
	ArrayIndexOutOfBoundsException() {}
};

}

#endif
