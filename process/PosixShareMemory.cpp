#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "PosixShareMemory.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ByteArray.hpp"
#include "Error.hpp"
#include "InitializeException.hpp"

//#define DEBUG_SHAREMEM_DUMP

namespace obotcha {

_PosixShareMemory::_PosixShareMemory(String name,int length,int type) {
    mName = name;
    size = length;
    mType = type;
    
    shareMemoryFd = shm_open(mName->toChars(),mType, S_IWUSR|S_IRUSR);
    if(shareMemoryFd == -1) {
        if(errno == ENOENT) {
            shareMemoryFd = shm_open(mName->toChars(),mType|O_CREAT|O_EXCL, S_IWUSR|S_IRUSR);
            struct stat ss;
            fstat(shareMemoryFd,&ss);
            
            if(ss.st_size < size) {
                if(ftruncate(shareMemoryFd, size) == -1) {
                    Trigger(InitializeException,"create share memory failed");
                }
            }
        }

        if(shareMemoryFd == -1) {
            Trigger(InitializeException,"create share memory failed");
        }
    }

    if(mType == Type::Read) {
        mPtr = (char *)mmap(NULL,size,PROT_READ,MAP_SHARED,shareMemoryFd,0);
    } else {
        mPtr = (char *)mmap(NULL,size,PROT_READ|PROT_WRITE,MAP_SHARED,shareMemoryFd,0);
    }
    
    if(mPtr == nullptr) {
        Trigger(InitializeException,"mmap share memory failed");
    }
}

int _PosixShareMemory::write(ByteArray arr) {
    if(arr->size() > size) {
        return -EINVAL;
    }

    if(mPtr != nullptr) {
        memcpy(mPtr,arr->toValue(),arr->size());
        return 0;
    }

    return -1;
}

int _PosixShareMemory::write(int index,ByteArray arr) {
    if((index + arr->size()) > size) {
        return -EINVAL;
    }

    if(mPtr != nullptr) {
        memcpy(&mPtr[index],arr->toValue(),arr->size());
        return 0;
    }

    return -1;
}

int _PosixShareMemory::write(int index,char v) {
    if(index >= size) {
        return -EINVAL;
    }

    if(mPtr != nullptr) {
        mPtr[index] = v;
        return 0;
    }

    return -1;
}

int _PosixShareMemory::read(ByteArray arr) {
    return read(0,arr);
}

int _PosixShareMemory::read(int index,ByteArray arr) {
    if(index >= size) {
        return -EINVAL;
    }

    int ll = (arr->size() + index) > size?size:(arr->size() + index);
    memcpy(arr->toValue(),mPtr,ll);
    return ll;
}

int _PosixShareMemory::read(int index) {
    if(index >= size) {
        return -EINVAL;
    }
    
    if(mPtr != nullptr) {
        return mPtr[index];
    }

    return -1;
}

void _PosixShareMemory::clear() {
    shm_unlink(mName->toChars());
}

void _PosixShareMemory::close() {
    if(mPtr != nullptr) {
        munmap(mPtr,size);
        mPtr = nullptr;
    }

    if(shareMemoryFd != -1) {
        ::close(shareMemoryFd);
        shareMemoryFd = -1;
    }
}

int _PosixShareMemory::getChannel() {
    return shareMemoryFd;
}

_PosixShareMemory::~_PosixShareMemory() {
    close();
}

}


