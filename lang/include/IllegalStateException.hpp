#ifndef __OBOTCHA_ILLEGAL_STATE_EXCEPTION_HPP__
#define __OBOTCHA_ILLEGAL_STATE_EXCEPTION_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Exception.hpp"

namespace obotcha {

DECLARE_EXCEPTION(IllegalStateException) {
public:
	IllegalStateException(const char * str):Exception(str){}
	IllegalStateException(String str):Exception(str) {}
};

}

#endif
