#ifndef __TRANSFORM_EXCEPTION_HPP__
#define __TRANSFORM_EXCEPTION_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Exception.hpp"

namespace obotcha {

class TransformException: public Exception {
public:
    TransformException(String);

    TransformException(const char *v);

private:
    static const String EXCEPTION_TAG;
};

}

#endif