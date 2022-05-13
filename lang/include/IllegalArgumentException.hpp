#ifndef __OBOTCHA_ILLEGAL_ARGUMENT_EXCEPTION_HPP__
#define __OBOTCHA_ILLEGAL_ARGUMENT_EXCEPTION_HPP__

#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"

#include "String.hpp"
#include "Exception.hpp"

namespace obotcha {

DECLARE_EXCEPTION(IllegalArgumentException) {
public:
	IllegalArgumentException() {}
};

}

#endif
