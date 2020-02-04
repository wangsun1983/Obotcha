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

const String FileNotFoundException::EXCEPTION_TAG = createString("File Not Found Exception:");

FileNotFoundException::FileNotFoundException(String v):Exception{v} {
    mErrInfo = EXCEPTION_TAG->append(v);
}

FileNotFoundException::FileNotFoundException(const char *v):FileNotFoundException{createString(v)} {
}

}
