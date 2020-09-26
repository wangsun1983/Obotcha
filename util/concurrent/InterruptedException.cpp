#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Exception.hpp"
#include "InterruptedException.hpp"

namespace obotcha {

const String InterruptedException::EXCEPTION_TAG = createString("InterruptedException:");

InterruptedException::InterruptedException(String v):Exception{v} {
    mErrInfo = EXCEPTION_TAG->append(v);
}

InterruptedException::InterruptedException(const char * v):Exception{v} {
    mErrInfo = EXCEPTION_TAG->append(v);
}  

}
