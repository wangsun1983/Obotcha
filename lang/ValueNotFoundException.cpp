#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Exception.hpp"
#include "ValueNotFoundException.hpp"

namespace obotcha {

const String _ValueNotFoundException::EXCEPTION_TAG = createString("Value Not Found Exception:");

_ValueNotFoundException::_ValueNotFoundException(String v):_Exception{v} {
    mErrInfo = EXCEPTION_TAG->append(v);
}

_ValueNotFoundException::_ValueNotFoundException(const char * v):_ValueNotFoundException{createString(v)} {
}

}
