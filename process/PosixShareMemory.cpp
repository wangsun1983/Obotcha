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

namespace obotcha {

_PosixShareMemory::_PosixShareMemory(String name,int length,int type) {
    mName = name;
    size = length;
    mType = type;

    mPtr = nullptr;
}

bool _PosixShareMemory::init() {
    shareMemoryFd = shm_open(mName->toChars(),mType, S_IWUSR|S_IRUSR);
    while(shareMemoryFd == -1) {
        if(errno == ENOENT) {
            printf("share memory create \n");
            shareMemoryFd = shm_open(mName->toChars(),mType|O_CREAT, S_IWUSR|S_IRUSR);
            //if(mType != PosixShareMemoryRead) {
            //if(ftruncate(shareMemoryFd, size) == -1) {
            //    printf("share memory ftruncat failed \n");
            //    return false;
            //}
            //}

            continue;
        }
        printf("mq_send errno: %s,id is %d \n",strerror(errno),errno);
        printf("shareMemoryFd is -1 \n");
        return false;
    }

    struct stat ss;
    fstat(shareMemoryFd,&ss);
    printf("share file size is %d \n",ss.st_size);
    if(ss.st_size < size && mType == PosixShareMemoryWriteRead) {
        printf("shareMemoryFd ftruncate \n");
        if(ftruncate(shareMemoryFd, size) == -1) {
            printf("share memory ftruncat failed \n");
            return false;
        }
    }

    printf("shareMemoryFd is %d,size is %d \n",shareMemoryFd,size);

    mPtr = (char *)mmap(NULL,size,PROT_READ|PROT_WRITE,MAP_SHARED,shareMemoryFd,0);
    
    close(shareMemoryFd);

    if(mPtr == nullptr) {
        printf("mmap failed \n");
        return false;
    }
}

bool _PosixShareMemory::write(ByteArray arr) {
    if(mPtr != nullptr) {
        char *v = arr->toValue();
        printf("write size is %d \n",arr->size());
        printf("write v[0] is %d \n",v[0]);
        printf("write v[1] is %d \n",v[1]);
        printf("write v[2] is %d \n",v[2]);
        printf("write v[3] is %d \n",v[3]);
        printf("write v[4] is %d \n",v[4]);

        memcpy(mPtr,arr->toValue(),arr->size());

        printf("mPtr v[0] is %d \n",mPtr[0]);
        printf("mPtr v[1] is %d \n",mPtr[1]);
        printf("mPtr v[2] is %d \n",mPtr[2]);
        printf("mPtr v[3] is %d \n",mPtr[3]);
        printf("mPtr v[4] is %d \n",mPtr[4]);

    }
}

int _PosixShareMemory::read(ByteArray arr) {
    if(mPtr != nullptr) {
        int ll = arr->size() > size?size:arr->size();
        printf("mPtr[0] is %d \n",mPtr[0]);
        printf("mPtr[1] is %d \n",mPtr[1]);
        printf("mPtr[2] is %d \n",mPtr[2]);
        memcpy(arr->toValue(),mPtr,ll);
    }
}

_PosixShareMemory::~_PosixShareMemory() {

}

}


