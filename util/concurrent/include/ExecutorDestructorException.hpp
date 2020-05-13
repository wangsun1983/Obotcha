#ifndef __OBOTCHA_EXECUTOR_DESTRUCTOR_EXCEPTION_HPP__
#define __OBOTCHA_EXECUTOR_DESTRUCTOR_EXCEPTION_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Exception.hpp"

namespace obotcha {

class ExecutorDestructorException:public Exception {
public:
    ExecutorDestructorException(String);

    ExecutorDestructorException(const char *);

private:
    static const String EXCEPTION_TAG;
};

}
#endif
