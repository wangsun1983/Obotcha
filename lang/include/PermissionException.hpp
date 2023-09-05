#ifndef __OBOTCHA_PERMISSION_EXCEPTION_HPP__
#define __OBOTCHA_PERMISSION_EXCEPTION_HPP__

#include "Exception.hpp"

namespace obotcha {

DECLARE_EXCEPTION(PermissionException){
public:
	PermissionException() = default;
};

}

#endif
