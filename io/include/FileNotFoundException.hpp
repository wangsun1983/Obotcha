#ifndef __OBOTCHA_FILE_NOT_FOUND_EXCEPTION_HPP__
#define __OBOTCHA_FILE_NOT_FOUND_EXCEPTION_HPP__

#include "Exception.hpp"

namespace obotcha {

DECLARE_EXCEPTION(FileNotFoundException) {
public:
	FileNotFoundException() = default;
};

}
#endif
