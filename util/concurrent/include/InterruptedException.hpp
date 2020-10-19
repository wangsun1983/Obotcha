#ifndef __OBOTCHA_INTERRUPTED_EXCEPTION_HPP__
#define __OBOTCHA_INTERRUPTED_EXCEPTION_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Exception.hpp"

namespace obotcha {

DECLARE_EXCEPTION(InterruptedException) {
public:
	InterruptedException(const char * str):Exception(str){}
	InterruptedException(String str):Exception(str) {}
};

}
#endif
