#ifndef __OBOTCHA_FILE_NOT_FOUND_EXCEPTION_HPP__
#define __OBOTCHA_FILE_NOT_FOUND_EXCEPTION_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Exception.hpp"

namespace obotcha {

DECLARE_EXCEPTION(FileNotFoundException) {
public:
	FileNotFoundException(const char * str):Exception(str){}
	FileNotFoundException(String str):Exception(str) {}
};

}
#endif
