#ifndef __OBOTCHA_REFLECT_EXCEPTION_HPP__
#define __OBOTCHA_REFLECT_EXCEPTION_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Exception.hpp"

namespace obotcha {

class ReflectException:public Exception {
public:
    ReflectException(String);

    ReflectException(const char *v);

private:
    static const String EXCEPTION_TAG;
};

}

#endif
