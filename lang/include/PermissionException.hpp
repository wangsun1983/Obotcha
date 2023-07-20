#ifndef __OBOTCHA_PERMISSION_EXCEPTION_HPP__
#define __OBOTCHA_PERMISSION_EXCEPTION_HPP__

#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "Object.hpp"

#include "Exception.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_EXCEPTION(PermissionException){
public:
	PermissionException() = default;
};

}

#endif
