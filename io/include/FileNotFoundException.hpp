#ifndef __OBOTCHA_FILE_NOT_FOUND_EXCEPTION_HPP__
#define __OBOTCHA_FILE_NOT_FOUND_EXCEPTION_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Exception.hpp"

namespace obotcha {

class FileNotFoundException: public Exception {
public:
    FileNotFoundException(String);
    
    FileNotFoundException(const char *);
private:
    static const String EXCEPTION_TAG;
};

}
#endif
