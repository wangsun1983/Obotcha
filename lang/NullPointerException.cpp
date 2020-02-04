#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "NullPointerException.hpp"

namespace obotcha {

const String NullPointerException::EXCEPTION_TAG = createString("Null Pointer Exception:");

NullPointerException::NullPointerException(String v):Exception{v} {
    mErrInfo = EXCEPTION_TAG->append(v);
}

NullPointerException::NullPointerException(const char* v):NullPointerException{createString(v)} {
}


}
