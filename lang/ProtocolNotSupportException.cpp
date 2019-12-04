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

const String _ProtocolNotSupportException::EXCEPTION_TAG = createString("Protocol Not Support Exception:");

_ProtocolNotSupportException::_ProtocolNotSupportException(String v):_Exception{v} {
    mErrInfo = EXCEPTION_TAG->append(v);
}

_ProtocolNotSupportException::_ProtocolNotSupportException(const char * v):_ProtocolNotSupportException{createString(v)} {
}

}
