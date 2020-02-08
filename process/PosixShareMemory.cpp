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

//#define DEBUG_SHAREMEM_DUMP

namespace obotcha {

_PosixShareMemory::_PosixShareMemory(String name,int length,int type) {
    mName = name;
    size = length;
    mType = type;
    isCreated = false;

    mPtr = nullptr;
}

int _PosixShareMemory::init() {
    shareMemoryFd = shm_open(mName->toChars(),mType, S_IWUSR|S_IRUSR);
    while(shareMemoryFd == -1) {
        if(errno == ENOENT) {
            shareMemoryFd = shm_open(mName->toChars(),mType|O_CREAT|O_EXCL, S_IWUSR|S_IRUSR);
            continue;
        }

        return -OpenFail;
    }

    struct stat ss;
    fstat(shareMemoryFd,&ss);
    
    if(ss.st_size < size) {
        if(ftruncate(shareMemoryFd, size) == -1) {
            return false;
        }
    }

    if(mType == PosixShareMemoryRead) {
        mPtr = (char *)mmap(NULL,size,PROT_READ,MAP_SHARED,shareMemoryFd,0);
    } else {
        mPtr = (char *)mmap(NULL,size,PROT_READ|PROT_WRITE,MAP_SHARED,shareMemoryFd,0);
    }
    
    close(shareMemoryFd);

    if(mPtr == nullptr) {
        return -MmapFail;
    }

    isCreated = true;

    return 0;
}

int _PosixShareMemory::write(ByteArray arr) {
    if(!isCreated) {
        return -NotCreate;
    }

    if(arr->size() > size) {
        return -OverSize;
    }

    memcpy(mPtr,arr->toValue(),arr->size());

    return 0;
}

int _PosixShareMemory::write(int index,ByteArray arr) {
    if(!isCreated) {
        return -NotCreate;
    }

    if((index + arr->size()) > size) {
        return -OverSize;
    }

    memcpy(&mPtr[index],arr->toValue(),arr->size());

    return 0;
}

int _PosixShareMemory::write(int index,char v) {
    if(!isCreated) {
        return -NotCreate;
    }

    if(index >= size) {
        return -OverSize;
    }

    mPtr[index] = v;

    return 0;
}

int _PosixShareMemory::read(ByteArray arr) {
    if(!isCreated) {
        return -NotCreate;
    }

    int ll = arr->size() > size?size:arr->size();
    memcpy(arr->toValue(),mPtr,ll);

    return ll;
}

int _PosixShareMemory::read(int index,ByteArray arr) {
    if(!isCreated) {
        return -NotCreate;
    }

    if(index >= size) {
        return -OverSize;
    }

    int ll = (arr->size() + index) > size?size:(arr->size() + index);
    memcpy(arr->toValue(),mPtr,ll);
    return ll;
}

int _PosixShareMemory::read(int index) {
    if(!isCreated) {
        return -NotCreate;
    }

    if(index >= size) {
        return -OverSize;
    }

    return mPtr[index];
}

void _PosixShareMemory::destroy() {
    shm_unlink(mName->toChars());
}

void _PosixShareMemory::release() {
    //shm_unlink(mName->toChars());
}

void _PosixShareMemory::clean() {
    //shm_unlink(mName->toChars());
}

_PosixShareMemory::~_PosixShareMemory() {
    //shm_unlink(mName->toChars());
}

}


