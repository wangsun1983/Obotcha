#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Exception.hpp"
#include "MethodNotSupportException.hpp"

namespace obotcha {

const String MethodNotSupportException::EXCEPTION_TAG = createString("Method Not Support Exception:");

MethodNotSupportException::MethodNotSupportException(String v):Exception{v} {
    mErrInfo = EXCEPTION_TAG->append(v);
}

MethodNotSupportException::MethodNotSupportException(const char * v):MethodNotSupportException{createString(v)} {
}

}
