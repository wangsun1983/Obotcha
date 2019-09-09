#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InitializeException.hpp"

namespace obotcha {

const String _InitializeException::EXCEPTION_TAG = createString("Initialize Exception:");

_InitializeException::_InitializeException(String v):_Exception{v} {
    mErrInfo = EXCEPTION_TAG->append(v);
}

}

