#ifndef __OBOTCHA_INVALID_KEY_EXCEPTION_HPP__
#define __OBOTCHA_INVALID_KEY_EXCEPTION_HPP__

#include "Exception.hpp"

namespace obotcha {

DECLARE_EXCEPTION(InvalidKeyException){
public:
	InvalidKeyException() = default;
};

}

#endif
