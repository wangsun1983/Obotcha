#ifndef __OBOTCHA_ILLEGAL_ARGUMENT_EXCEPTION_HPP__
#define __OBOTCHA_ILLEGAL_ARGUMENT_EXCEPTION_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Exception.hpp"

namespace obotcha {

class IllegalArgumentException:public Exception {
public:
    IllegalArgumentException(String);

    IllegalArgumentException(const char *v);

private:
    static const String EXCEPTION_TAG;
};

}

#endif
