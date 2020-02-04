#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Exception.hpp"
#include "ProtocolNotSupportException.hpp"

namespace obotcha {

const String ProtocolNotSupportException::EXCEPTION_TAG = createString("Protocol Not Support Exception:");

ProtocolNotSupportException::ProtocolNotSupportException(String v):Exception{v} {
    mErrInfo = EXCEPTION_TAG->append(v);
}

ProtocolNotSupportException::ProtocolNotSupportException(const char * v):ProtocolNotSupportException{createString(v)} {
}

}
