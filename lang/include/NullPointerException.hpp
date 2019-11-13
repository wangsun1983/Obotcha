#ifndef __NULL_POINTER_EXCEPTION_HPP__
#define __NULL_POINTER_EXCEPTION_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Exception.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(NullPointerException) EXTENDS(Exception) {
public:
    _NullPointerException(String);

    _NullPointerException(const char *v);

private:
    static const String EXCEPTION_TAG;
};

}

#endif
