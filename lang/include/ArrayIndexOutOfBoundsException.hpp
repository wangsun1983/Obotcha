#ifndef __ARRAY_INDEX_OUTOF_BOUNDS_EXCEPTION_HPP__
#define __ARRAY_INDEX_OUTOF_BOUNDS_EXCEPTION_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Exception.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(ArrayIndexOutOfBoundsException) EXTENDS(Exception) {
public:
    _ArrayIndexOutOfBoundsException(String,int,int);
    _ArrayIndexOutOfBoundsException(const char *,int,int);
    _ArrayIndexOutOfBoundsException(const char *);

private:
    static const String EXCEPTION_TAG;
    static const String MAX_SIZE;
    static const String CURRENT_INDEX;
};

}

#endif
