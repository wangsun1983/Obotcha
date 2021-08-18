#ifndef __OBOTCHA_TIME_OUT_EXCEPTION_HPP__
#define __OBOTCHA_TIME_OUT_EXCEPTION_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>
#include <string>

#include "Object.hpp"

#include "String.hpp"
#include "Exception.hpp"

namespace obotcha {

DECLARE_EXCEPTION(TimeOutException) {
public:
	TimeOutException(const char * str):Exception(str){}
	TimeOutException(String str):Exception(str) {}
};

}

#endif
