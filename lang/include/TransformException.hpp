#ifndef __OBOTCHA_TRANSFORM_EXCEPTION_HPP__
#define __OBOTCHA_TRANSFORM_EXCEPTION_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Exception.hpp"

namespace obotcha {

DECLARE_EXCEPTION(TransformException) {
public:
	TransformException(const char * str):Exception(str){}
	TransformException(String str):Exception(str) {}
};

}

#endif
