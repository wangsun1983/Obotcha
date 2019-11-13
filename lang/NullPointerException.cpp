#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "NullPointerException.hpp"

namespace obotcha {

const String _NullPointerException::EXCEPTION_TAG = createString("Null Pointer Exception:");

_NullPointerException::_NullPointerException(String v):_Exception{v} {
    mErrInfo = EXCEPTION_TAG->append(v);
}

_NullPointerException::_NullPointerException(const char* v):_NullPointerException{createString(v)} {
}


}
