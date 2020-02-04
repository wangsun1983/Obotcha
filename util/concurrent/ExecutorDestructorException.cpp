#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Exception.hpp"
#include "ExecutorDestructorException.hpp"

namespace obotcha {

const String ExecutorDestructorException::EXCEPTION_TAG = createString("Destructor befor shutdown:");

ExecutorDestructorException::ExecutorDestructorException(String v):Exception{v} {
    mErrInfo = EXCEPTION_TAG->append(v);
}

ExecutorDestructorException::ExecutorDestructorException(const char * v):Exception{v} {
    mErrInfo = EXCEPTION_TAG->append(v);
}  

}
