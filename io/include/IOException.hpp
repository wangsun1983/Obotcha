#ifndef __OBOTCHA_IO_EXCEPTION_HPP__
#define __OBOTCHA_IO_EXCEPTION_HPP__

#include "Exception.hpp"

namespace obotcha {

DECLARE_EXCEPTION(IOException) {
public:
	IOException() = default;
};

}
#endif
