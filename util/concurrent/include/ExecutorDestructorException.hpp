#ifndef __EXECUTOR_DESTRUCTOR_EXCEPTION_HPP__
#define __EXECUTOR_DESTRUCTOR_EXCEPTION_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Exception.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(ExecutorDestructorException) EXTENDS(Exception) {
public:
    _ExecutorDestructorException(String);

    _ExecutorDestructorException(const char *);

private:
    static const String EXCEPTION_TAG;
};

}
#endif
