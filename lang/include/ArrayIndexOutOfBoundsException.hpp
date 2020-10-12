#ifndef __OBOTCHA_ARRAY_INDEX_OUTOF_BOUNDS_EXCEPTION_HPP__
#define __OBOTCHA_ARRAY_INDEX_OUTOF_BOUNDS_EXCEPTION_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Exception.hpp"

namespace obotcha {

DECLARE_EXCEPTION(ArrayIndexOutOfBoundsException){
public:
	ArrayIndexOutOfBoundsException(const char * str):Exception(str){}
	ArrayIndexOutOfBoundsException(String str):Exception(str) {}
};

}

#endif
