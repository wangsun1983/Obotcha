#ifndef __OBOTCHA_NULL_POINTER_EXCEPTION_HPP__
#define __OBOTCHA_NULL_POINTER_EXCEPTION_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Exception.hpp"

namespace obotcha {

DECLARE_EXCEPTION(NullPointerException) {
public:
	NullPointerException(const char * str):Exception(str){}
	NullPointerException(String str):Exception(str) {}
};

}

#endif
