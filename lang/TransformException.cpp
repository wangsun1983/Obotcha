#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "TransformException.hpp"

namespace obotcha {

const String TransformException::EXCEPTION_TAG = createString("Transform Exception:");

TransformException::TransformException(String v):Exception{v} {
    mErrInfo = EXCEPTION_TAG->append(v);
}

TransformException::TransformException(const char* v):TransformException{createString(v)} {
}


}
