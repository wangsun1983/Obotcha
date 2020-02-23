#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "IllegalStateException.hpp"

namespace obotcha {

const String IllegalStateException::EXCEPTION_TAG = createString("IllegalState Exception:");

IllegalStateException::IllegalStateException(String v):Exception{v} {
    mErrInfo = EXCEPTION_TAG->append(v);
}

IllegalStateException::IllegalStateException(const char* v):IllegalStateException{createString(v)} {
}


}
