#ifndef __OBOTCHA_HTTP_INTERNAL_EXCEPTION_HPP__
#define __OBOTCHA_HTTP_INTERNAL_EXCEPTION_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Exception.hpp"

namespace obotcha {

DECLARE_EXCEPTION(HttpInternalException) {
public:
	HttpInternalException(const char * str):Exception(str){}
	HttpInternalException(String str):Exception(str) {}
};

}

#endif
