#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Exception.hpp"
#include "ResultDuplicateException.hpp"

namespace obotcha {

const String ResultDuplicateException::EXCEPTION_TAG = createString("Duplicate Result:");

ResultDuplicateException::ResultDuplicateException(String v):Exception{v} {
    mErrInfo = EXCEPTION_TAG->append(v);
}

ResultDuplicateException::ResultDuplicateException(const char * v):Exception{v} {
    mErrInfo = EXCEPTION_TAG->append(v);
}  

}
