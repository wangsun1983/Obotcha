#ifndef __OBOTCHA_ARRAY_INDEX_OUTOF_BOUNDS_EXCEPTION_HPP__
#define __OBOTCHA_ARRAY_INDEX_OUTOF_BOUNDS_EXCEPTION_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Exception.hpp"

namespace obotcha {

class ArrayIndexOutOfBoundsException:public Exception {
public:
    ArrayIndexOutOfBoundsException(String,int,int);
    ArrayIndexOutOfBoundsException(const char *,int,int);
    ArrayIndexOutOfBoundsException(const char *);

private:
    static const String EXCEPTION_TAG;
    static const String MAX_SIZE;
    static const String CURRENT_INDEX;
};

}

#endif
