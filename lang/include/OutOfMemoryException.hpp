#ifndef __OBOTCHA_OUT_OF_MEMORY_EXCEPTION_HPP__
#define __OBOTCHA_OUT_OF_MEMORY_EXCEPTION_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Exception.hpp"

namespace obotcha {

DECLARE_EXCEPTION(OutOfMemoryException){
public:
	OutOfMemoryException(const char * str):Exception(str){}
	OutOfMemoryException(String str):Exception(str) {}
};

}

#endif
