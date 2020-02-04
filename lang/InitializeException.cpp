#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InitializeException.hpp"

namespace obotcha {

const String InitializeException::EXCEPTION_TAG = createString("Initialize Exception:");

InitializeException::InitializeException(String v):Exception{v} {
    mErrInfo = EXCEPTION_TAG->append(v);
}

InitializeException::InitializeException(const char* v):InitializeException{createString(v)} {
}


}

