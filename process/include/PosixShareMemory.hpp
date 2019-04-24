#ifndef __POSIX_SHARE_MEMORY_HPP__
#define __POSIX_SHARE_MEMORY_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <mqueue.h>
#include <fstream>


#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ByteArray.hpp"
#include "String.hpp"

namespace obotcha {

enum PosixShareMemoryType {
    PosixShareMemoryRead = O_RDONLY,
    PosixShareMemoryWriteRead = O_RDWR,
};

DECLARE_SIMPLE_CLASS(PosixShareMemory) {
public:

    _PosixShareMemory(String,int,int type);

    bool init();

    bool write(ByteArray);

    int read(ByteArray);

    ~_PosixShareMemory();

private:
    String mName;

    int size;

    int shareMemoryFd;

    char *mPtr;

    int mType;
   
};

}
#endif
