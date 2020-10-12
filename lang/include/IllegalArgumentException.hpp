#ifndef __OBOTCHA_ILLEGAL_ARGUMENT_EXCEPTION_HPP__
#define __OBOTCHA_ILLEGAL_ARGUMENT_EXCEPTION_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Exception.hpp"

namespace obotcha {

DECLARE_EXCEPTION(IllegalArgumentException) {
public:
	IllegalArgumentException(const char * str):Exception(str){}
	IllegalArgumentException(String str):Exception(str) {}
};

}

#endif
