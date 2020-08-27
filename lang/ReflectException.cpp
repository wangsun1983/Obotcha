#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Exception.hpp"
#include "ReflectException.hpp"

namespace obotcha {

const String ReflectException::EXCEPTION_TAG = createString("Reflect Exception:");

ReflectException::ReflectException(String v):Exception{v} {
    mErrInfo = EXCEPTION_TAG->append(v);
}

ReflectException::ReflectException(const char * v):ReflectException{createString(v)} {
}

}
