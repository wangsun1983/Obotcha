#ifndef __FILE_NOT_FOUND_EXCEPTION_HPP__
#define __FILE_NOT_FOUND_EXCEPTION_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Exception.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(FileNotFoundException) EXTENDS(Exception) {
public:
    _FileNotFoundException(String);
    
    _FileNotFoundException(const char *);
private:
    static const String EXCEPTION_TAG;
};

}
#endif
