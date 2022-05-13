#ifndef __OBOTCHA_PADDING_NOT_SUPPORT_EXCEPTION_HPP__
#define __OBOTCHA_PADDING_NOT_SUPPORT_EXCEPTION_HPP__

#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "Object.hpp"

#include "Exception.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_EXCEPTION(PaddingNotSupportException){
public:
	PaddingNotSupportException() {}
};

}

#endif
