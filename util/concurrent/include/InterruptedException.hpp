#ifndef __OBOTCHA_INTERRUPTED_EXCEPTION_HPP__
#define __OBOTCHA_INTERRUPTED_EXCEPTION_HPP__

#include "Exception.hpp"

namespace obotcha {

DECLARE_EXCEPTION(InterruptedException) {
public:
	InterruptedException() = default;
};

}
#endif
