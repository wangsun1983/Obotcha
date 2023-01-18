#include <fcntl.h>
#include <sys/mman.h>

#include "ShareMemory.hpp"
#include "ByteArray.hpp"
#include "InitializeException.hpp"

//#define DEBUG_SHAREMEM_DUMP

namespace obotcha {

_ShareMemory::_ShareMemory(String name,int length,int type) {
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

int _ShareMemory::write(ByteArray arr) {
    if(arr->size() > size) {
        return -EINVAL;
    }

    if(mPtr != nullptr) {
        memcpy(mPtr,arr->toValue(),arr->size());
        return 0;
    }

    return -1;
}

int _ShareMemory::write(int index,ByteArray arr) {
    if((index + arr->size()) > size) {
        return -EINVAL;
    }

    if(mPtr != nullptr) {
        memcpy(&mPtr[index],arr->toValue(),arr->size());
        return 0;
    }

    return -1;
}

int _ShareMemory::write(int index,char v) {
    if(index >= size) {
        return -EINVAL;
    }

    if(mPtr != nullptr) {
        mPtr[index] = v;
        return 0;
    }

    return -1;
}

int _ShareMemory::read(ByteArray arr) {
    return read(0,arr);
}

int _ShareMemory::read(int index,ByteArray arr) {
    if(index >= size) {
        return -EINVAL;
    }

    int len = -1;
    if(mPtr != nullptr) {
        len = (arr->size() + index) > size?size:(arr->size() + index);
        memcpy(arr->toValue(),mPtr,len);
    }
    return len;
}

int _ShareMemory::read(int index) {
    if(index >= size) {
        return -EINVAL;
    }
    
    if(mPtr != nullptr) {
        return mPtr[index];
    }

    return -1;
}

void _ShareMemory::clear() {
    //shm_unlink(mName->toChars());
    //ftruncate(shareMemoryFd, size);
    memset(mPtr,0,size);
}

void _ShareMemory::close() {
    if(mPtr != nullptr) {
        munmap(mPtr,size);
        mPtr = nullptr;
    }

    if(shareMemoryFd != -1) {
        shm_unlink(mName->toChars());
        ::close(shareMemoryFd);
        shareMemoryFd = -1;
    }
}

int _ShareMemory::getChannel() {
    return shareMemoryFd;
}

_ShareMemory::~_ShareMemory() {
    close();
}

}


