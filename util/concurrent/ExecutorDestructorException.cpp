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

const String _ExecutorDestructorException::EXCEPTION_TAG = createString("Destructor befor shutdown:");

_ExecutorDestructorException::_ExecutorDestructorException(String v):_Exception{v} {
    mErrInfo = EXCEPTION_TAG->append(v);
}

_ExecutorDestructorException::_ExecutorDestructorException(const char * v):_Exception{v} {
    mErrInfo = EXCEPTION_TAG->append(v);
}  

}
