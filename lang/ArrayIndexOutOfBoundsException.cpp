#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"

namespace obotcha {

const String _ArrayIndexOutOfBoundsException::EXCEPTION_TAG = createString("Array Index OutOf Bounds Exception:");
const String _ArrayIndexOutOfBoundsException::MAX_SIZE = createString("Max Size is :");
const String _ArrayIndexOutOfBoundsException::CURRENT_INDEX = createString(" ;Current Index is :");

_ArrayIndexOutOfBoundsException::_ArrayIndexOutOfBoundsException(String v,int maxsize,int index):_Exception{v}{
    mErrInfo = EXCEPTION_TAG->append(v)
                            ->append(MAX_SIZE)
                            ->append(createString(maxsize))
                            ->append(CURRENT_INDEX)
                            ->append(createString(index));
}


}
