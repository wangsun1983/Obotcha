#ifndef __PROTOCOL_NOT_SUPPORT_EXCEPTION_HPP__
#define __PROTOCOL_NOT_SUPPORT_EXCEPTION_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Exception.hpp"

namespace obotcha {

class ProtocolNotSupportException:public Exception {
public:
    ProtocolNotSupportException(String);

    ProtocolNotSupportException(const char *v);

private:
    static const String EXCEPTION_TAG;
};

}

#endif
