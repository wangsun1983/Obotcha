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

const String _MethodNotSupportException::EXCEPTION_TAG = createString("Method Not Support Exception:");

_MethodNotSupportException::_MethodNotSupportException(String v):_Exception{v} {
    mErrInfo = EXCEPTION_TAG->append(v);
}

_MethodNotSupportException::_MethodNotSupportException(const char * v):_MethodNotSupportException{createString(v)} {
}

}
