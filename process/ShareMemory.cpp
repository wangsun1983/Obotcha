#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include "ShareMemory.hpp"
#include "ByteArray.hpp"
#include "InitializeException.hpp"
#include "Inspect.hpp"
#include "System.hpp"

namespace obotcha {

_ShareMemory::_ShareMemory(String name,size_t length,Type type):
                                    mName(name),mSize(length),mType(type) {
   
    mShareMemoryFd = shm_open(mName->toChars(),static_cast<int>(mType), S_IWUSR|S_IRUSR);
    Panic(mShareMemoryFd == -1,InitializeException,"create share memory failed,error is %s,path is %s",strerror(errno),mName->toChars())

    int prot = PROT_READ;
    prot |= ((mType == Type::Read)?1:PROT_WRITE);
    mPtr = (char *)mmap(nullptr,mSize,prot,MAP_SHARED,mShareMemoryFd,0);
    Panic(mPtr == nullptr,InitializeException,"mmap share memory failed")
}

int _ShareMemory::write(ByteArray arr) {
    Inspect(arr->size() > mSize,-EINVAL)
    if(mPtr != nullptr) {
        memcpy(mPtr,arr->toValue(),arr->size());
    }
    return (mPtr == nullptr)?-1:0;
}

int _ShareMemory::write(int index,ByteArray arr) {
    Inspect((index + arr->size()) > mSize,-EINVAL)
    if(mPtr != nullptr) {
        memcpy(&mPtr[index],arr->toValue(),arr->size());
    }
    return (mPtr == nullptr)?-1:0;
}

int _ShareMemory::write(int index,char v) {
    Inspect(index >= mSize,-EINVAL)
    if(mPtr != nullptr) {
        mPtr[index] = v;
    }
    return (mPtr == nullptr)?-1:0;
}

int _ShareMemory::read(ByteArray arr) const {
    return read(0,arr);
}

int _ShareMemory::read(int index,ByteArray arr) const {
    Inspect(index >= mSize,-EINVAL)
    int len = -1;
    if(mPtr != nullptr) {
        len = (arr->size() + index) > mSize?mSize:(arr->size() + index);
        memcpy(arr->toValue(),mPtr,len);
    }
    return len;
}

int _ShareMemory::read(int index) const {
    Inspect(index >= mSize, -EINVAL)
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
        ::close(mShareMemoryFd);
        mShareMemoryFd = -1;
    }
}

int _ShareMemory::Create(String name,size_t size) {
    auto fd = shm_open(name->toChars(),
                      O_RDWR|O_CREAT|O_EXCL, S_IWUSR|S_IRUSR);
    
    if(ftruncate(fd, size) == -1) {
       return -1;
    }

    ::close(fd);
    return 0;
}

int _ShareMemory::Clear(String name) {
    return shm_unlink(name->toChars());
}

int _ShareMemory::getChannel() const {
    return mShareMemoryFd;
}

_ShareMemory::~_ShareMemory() {
    close();
}

}


