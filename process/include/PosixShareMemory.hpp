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

DECLARE_CLASS(PosixShareMemory) {
public:
    enum Type {
        Read = O_RDONLY,
        WriteRead = O_RDWR,
    };

    _PosixShareMemory(String,int,int type);

    int write(ByteArray);

    int write(int index,ByteArray);

    int write(int index,char v);

    int read(ByteArray);

    int read(int index,ByteArray);

    int read(int);

    void close();

    void clear();

    int getChannel();

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
