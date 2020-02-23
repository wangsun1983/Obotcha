#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "IllegalArgumentException.hpp"

namespace obotcha {

const String IllegalArgumentException::EXCEPTION_TAG = createString("IllegalArgument Exception:");

IllegalArgumentException::IllegalArgumentException(String v):Exception{v} {
    mErrInfo = EXCEPTION_TAG->append(v);
}

IllegalArgumentException::IllegalArgumentException(const char* v):IllegalArgumentException{createString(v)} {
}


}
