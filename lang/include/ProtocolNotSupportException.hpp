#ifndef __OBOTCHA_PROTOCOL_NOT_SUPPORT_EXCEPTION_HPP__
#define __OBOTCHA_PROTOCOL_NOT_SUPPORT_EXCEPTION_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Exception.hpp"

namespace obotcha {

DECLARE_EXCEPTION(ProtocolNotSupportException) {
public:
	ProtocolNotSupportException(const char * str):Exception(str){}
	ProtocolNotSupportException(String str):Exception(str) {}
};

}

#endif
