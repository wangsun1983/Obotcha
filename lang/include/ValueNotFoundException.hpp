#ifndef __VALUE_NOT_FOUND_EXCEPTION_HPP__
#define __VALUE_NOT_FOUND_EXCEPTION_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Exception.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(ValueNotFoundException) EXTENDS(Exception) {
public:
    _ValueNotFoundException(String);
    _ValueNotFoundException(const char *);

private:
    static const String EXCEPTION_TAG;
};

}

#endif
