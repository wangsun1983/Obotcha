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

#define DEBUG_SHAREMEM_DUMP

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

        return -PosixShmCreateFailed;
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
        //printf("mmap failed \n");
        return -PosixShmMapFailed;
    }

    isCreated = true;

    return 0;
}

int _PosixShareMemory::write(ByteArray arr) {
    if(!isCreated) {
        return -PosixShmNotCreate;
    }

    //if(mPtr != nullptr) {
        char *v = arr->toValue();
#ifdef DEBUG_SHAREMEM_DUMP
        printf("write size is %d \n",arr->size());
        printf("write v[0] is %d \n",v[0]);
        printf("write v[1] is %d \n",v[1]);
        printf("write v[2] is %d \n",v[2]);
        printf("write v[3] is %d \n",v[3]);
        printf("write v[4] is %d \n",v[4]);
#endif
        memcpy(mPtr,arr->toValue(),arr->size());

#ifdef DEBUG_SHAREMEM_DUMP
        printf("mPtr v[0] is %d \n",mPtr[0]);
        printf("mPtr v[1] is %d \n",mPtr[1]);
        printf("mPtr v[2] is %d \n",mPtr[2]);
        printf("mPtr v[3] is %d \n",mPtr[3]);
        printf("mPtr v[4] is %d \n",mPtr[4]);
#endif        
        return 0;
    //}

    //return false;
}

int _PosixShareMemory::write(int index,ByteArray v) {
    if(!isCreated) {
        return -PosixShmNotCreate;
    }
}

int _PosixShareMemory::write(int index,char v) {

}



int _PosixShareMemory::read(ByteArray arr) {
    if(!isCreated) {
        return -PosixShmNotCreate;
    }

    //if(mPtr != nullptr) {
        int ll = arr->size() > size?size:arr->size();
#ifdef DEBUG_SHAREMEM_DUMP        
        printf("mPtr[0] is %d \n",mPtr[0]);
        printf("mPtr[1] is %d \n",mPtr[1]);
        printf("mPtr[2] is %d \n",mPtr[2]);
#endif        
        memcpy(arr->toValue(),mPtr,ll);

        return ll;
    //}
    //return -1;
}

void _PosixShareMemory::destroy() {
    shm_unlink(mName->toChars());
}

void _PosixShareMemory::release() {
    shm_unlink(mName->toChars());
}

void _PosixShareMemory::clean() {
    shm_unlink(mName->toChars());
}

_PosixShareMemory::~_PosixShareMemory() {
    shm_unlink(mName->toChars());
}

}


