#include <fcntl.h>
#include <sys/mman.h>

#include "ShareMemory.hpp"
#include "ByteArray.hpp"
#include "InitializeException.hpp"
#include "Inspect.hpp"

namespace obotcha {

_ShareMemory::_ShareMemory(String name,int length,int type) {
    mName = name;
    mSize = length;
    mType = type;
    
    mShareMemoryFd = shm_open(mName->toChars(),mType, S_IWUSR|S_IRUSR);
    if(mShareMemoryFd == -1) {
        if(errno == ENOENT) {
            mShareMemoryFd = shm_open(mName->toChars(),mType|O_CREAT|O_EXCL, S_IWUSR|S_IRUSR);
            struct stat ss;
            fstat(mShareMemoryFd,&ss);
            
            if(ss.st_size < mSize) {
                if(ftruncate(mShareMemoryFd, mSize) == -1) {
                    Trigger(InitializeException,"create share memory failed");
                }
            }
        }
        Panic(mShareMemoryFd == -1,InitializeException,"create share memory failed");
    }

    uint64_t flags = PROT_READ;
    flags |= ((mType == Type::Read)?1:PROT_WRITE);
    mPtr = (char *)mmap(NULL,mSize,flags,MAP_SHARED,mShareMemoryFd,0);
    Panic(mPtr == nullptr,InitializeException,"mmap share memory failed");
}

int _ShareMemory::write(ByteArray arr) {
    Inspect(arr->size() > mSize,-EINVAL);
    if(mPtr != nullptr) {
        memcpy(mPtr,arr->toValue(),arr->size());
    }
    return (mPtr == nullptr)?-1:0;
}

int _ShareMemory::write(int index,ByteArray arr) {
    Inspect((index + arr->size()) > mSize,-EINVAL);
    if(mPtr != nullptr) {
        memcpy(&mPtr[index],arr->toValue(),arr->size());
    }
    return (mPtr == nullptr)?-1:0;
}

int _ShareMemory::write(int index,char v) {
    Inspect(index >= mSize,-EINVAL);
    if(mPtr != nullptr) {
        mPtr[index] = v;
    }
    return (mPtr == nullptr)?-1:0;
}

int _ShareMemory::read(ByteArray arr) {
    return read(0,arr);
}

int _ShareMemory::read(int index,ByteArray arr) {
    Inspect(index >= mSize,-EINVAL);
    int len = -1;
    if(mPtr != nullptr) {
        len = (arr->size() + index) > mSize?mSize:(arr->size() + index);
        memcpy(arr->toValue(),mPtr,len);
    }
    return len;
}

int _ShareMemory::read(int index) {
    Inspect(index >= mSize, -EINVAL);
    return (mPtr == nullptr)?-1:mPtr[index];
}

void _ShareMemory::clear() {
    memset(mPtr,0,mSize);
}

void _ShareMemory::close() {
    if(mPtr != nullptr) {
        munmap(mPtr,mSize);
        mPtr = nullptr;
    }

    if(mShareMemoryFd != -1) {
        shm_unlink(mName->toChars());
        ::close(mShareMemoryFd);
        mShareMemoryFd = -1;
    }
}

int _ShareMemory::getChannel() {
    return mShareMemoryFd;
}

_ShareMemory::~_ShareMemory() {
    close();
}

}

