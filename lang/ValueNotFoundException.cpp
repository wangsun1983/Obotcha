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

const String ValueNotFoundException::EXCEPTION_TAG = createString("Value Not Found Exception:");

ValueNotFoundException::ValueNotFoundException(String v):Exception{v} {
    mErrInfo = EXCEPTION_TAG->append(v);
}

ValueNotFoundException::ValueNotFoundException(const char * v):ValueNotFoundException{createString(v)} {
}

}
