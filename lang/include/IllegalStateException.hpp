#ifndef __ILLEGAL_STATE_EXCEPTION_HPP__
#define __ILLEGAL_STATE_EXCEPTION_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Exception.hpp"

namespace obotcha {

class IllegalStateException:public Exception {
public:
    IllegalStateException(String);

    IllegalStateException(const char *v);

private:
    static const String EXCEPTION_TAG;
};

}

#endif