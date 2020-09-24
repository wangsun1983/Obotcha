#ifndef __OBOTCHA_RESULT_DUPLICATE_EXCEPTION_HPP__
#define __OBOTCHA_RESULT_DUPLICATE_EXCEPTION_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Exception.hpp"

namespace obotcha {

class ResultDuplicateException:public Exception {
public:
    ResultDuplicateException(String);

    ResultDuplicateException(const char *);

private:
    static const String EXCEPTION_TAG;
};

}
#endif
