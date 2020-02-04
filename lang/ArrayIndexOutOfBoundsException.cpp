#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"

namespace obotcha {

const String ArrayIndexOutOfBoundsException::EXCEPTION_TAG = createString("Array Index OutOf Bounds Exception:");
const String ArrayIndexOutOfBoundsException::MAX_SIZE = createString("Max Size is :");
const String ArrayIndexOutOfBoundsException::CURRENT_INDEX = createString(" ;Current Index is :");

ArrayIndexOutOfBoundsException::ArrayIndexOutOfBoundsException(String v,int maxsize,int index):Exception{v}{
    mErrInfo = EXCEPTION_TAG->append(v)
                            ->append(MAX_SIZE)
                            ->append(createString(maxsize))
                            ->append(CURRENT_INDEX)
                            ->append(createString(index));
}

ArrayIndexOutOfBoundsException::ArrayIndexOutOfBoundsException(const char * v,int maxsize,int index)
                                :ArrayIndexOutOfBoundsException{createString(v),maxsize,index}{
}

ArrayIndexOutOfBoundsException::ArrayIndexOutOfBoundsException(const char *v) :Exception{v}{
    mErrInfo = EXCEPTION_TAG->append(v);
}

}
