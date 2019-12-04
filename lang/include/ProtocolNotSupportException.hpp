#ifndef __PROTOCOL_NOT_SUPPORT_EXCEPTION_HPP__
#define __PROTOCOL_NOT_SUPPORT_EXCEPTION_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Exception.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(ProtocolNotSupportException) EXTENDS(Exception) {
public:
    _ProtocolNotSupportException(String);

    _ProtocolNotSupportException(const char *v);

private:
    static const String EXCEPTION_TAG;
};

}

#endif
