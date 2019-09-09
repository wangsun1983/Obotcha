#ifndef __METHOD_NOT_SUPPORT_EXCEPTION_HPP__
#define __METHOD_NOT_SUPPORT_EXCEPTION_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Exception.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(MethodNotSupportException) EXTENDS(Exception) {
public:
    _MethodNotSupportException(String);

private:
    static const String EXCEPTION_TAG;
};

}

#endif
