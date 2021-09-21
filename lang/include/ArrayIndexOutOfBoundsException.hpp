#ifndef __OBOTCHA_ARRAY_INDEX_OUTOF_BOUNDS_EXCEPTION_HPP__
#define __OBOTCHA_ARRAY_INDEX_OUTOF_BOUNDS_EXCEPTION_HPP__

#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "Object.hpp"

#include "Exception.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_EXCEPTION(ArrayIndexOutOfBoundsException){
public: 
	ArrayIndexOutOfBoundsException(const char *str):Exception(str){} 
	ArrayIndexOutOfBoundsException(String str):Exception(str){}
};

}

#endif
