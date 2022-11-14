#ifndef __OBOTCHA_PADDING_NOT_SUPPORT_EXCEPTION_HPP__
#define __OBOTCHA_PADDING_NOT_SUPPORT_EXCEPTION_HPP__

#include "Exception.hpp"

namespace obotcha {

DECLARE_EXCEPTION(PaddingNotSupportException){
public:
	PaddingNotSupportException() {}
};

}

#endif
