#ifndef __OBOTCHA_METHOD_NOT_SUPPORT_EXCEPTION_HPP__
#define __OBOTCHA_METHOD_NOT_SUPPORT_EXCEPTION_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Exception.hpp"

namespace obotcha {

DECLARE_EXCEPTION(MethodNotSupportException) {
public:
	MethodNotSupportException(const char * str):Exception(str){}
	MethodNotSupportException(String str):Exception(str) {}
};

}

#endif
