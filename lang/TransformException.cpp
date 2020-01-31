#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "TransformException.hpp"

namespace obotcha {

const String _TransformException::EXCEPTION_TAG = createString("Transform Exception:");

_TransformException::_TransformException(String v):_Exception{v} {
    mErrInfo = EXCEPTION_TAG->append(v);
}

_TransformException::_TransformException(const char* v):_TransformException{createString(v)} {
}


}
