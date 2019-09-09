#ifndef __INITIALIZE_EXCEPTION_HPP__
#define __INITIALIZE_EXCEPTION_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Exception.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(InitializeException) EXTENDS(Exception) {
public:
    _InitializeException(String);

private:
    static const String EXCEPTION_TAG;
};

}

#endif
