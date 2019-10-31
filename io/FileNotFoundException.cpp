#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Exception.hpp"
#include "FileNotFoundException.hpp"

namespace obotcha {

const String _FileNotFoundException::EXCEPTION_TAG = createString("File Not Found Exception:");

_FileNotFoundException::_FileNotFoundException(String v):_Exception{v} {
    mErrInfo = EXCEPTION_TAG->append(v);
}

_FileNotFoundException::_FileNotFoundException(const char *v):_FileNotFoundException{createString(v)} {
}

}
