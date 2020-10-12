#ifndef __OBOTCHA_VALUE_NOT_FOUND_EXCEPTION_HPP__
#define __OBOTCHA_VALUE_NOT_FOUND_EXCEPTION_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Exception.hpp"

namespace obotcha {

DECLARE_EXCEPTION(ValueNotFoundException) {
public:
	ValueNotFoundException(const char * str):Exception(str){}
	ValueNotFoundException(String str):Exception(str) {}
};

}

#endif
