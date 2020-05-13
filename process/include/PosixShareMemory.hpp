#ifndef __OBOTCHA_POSIX_SHARE_MEMORY_HPP__
#define __OBOTCHA_POSIX_SHARE_MEMORY_HPP__

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

    int init();

    int write(ByteArray);

    int write(int index,ByteArray);

    int write(int index,char v);

    int read(ByteArray);

    int read(int index,ByteArray);

    int read(int);

    void destroy();

    void release();

    void clean();

    ~_PosixShareMemory();

private:
    String mName;

    int size;

    int shareMemoryFd;

    char *mPtr;

    int mType;

    bool isCreated;
   
};

}
#endif
