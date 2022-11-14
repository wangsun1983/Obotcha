#include <fcntl.h>

#include "MappedFile.hpp"
#include "MappedFileInputStream.hpp"
#include "MappedFileOutputStream.hpp"
#include "Log.hpp"
#include "InitializeException.hpp"

namespace obotcha {

//-------- MappedFile --------
_MappedFile::_MappedFile(String path,long size,int type,int flag) {
    File f = createFile(path);
    bool isNew = false;

    if(!f->exists()) {
        f->createNewFile();
        isNew = true;
    }

    int fd = -1;
    if(type == PROT_READ) {
        fd = ::open(f->getAbsolutePath()->toChars(),O_RDONLY);
    } else if(type == PROT_WRITE) {
        fd = ::open(f->getAbsolutePath()->toChars(),O_WRONLY);
    } else {
        fd = ::open(f->getAbsolutePath()->toChars(),O_RDWR);
    }

    if(isNew || f->length() == 0) {
        ftruncate(fd,size);
    }

    if(size == 0) {
        mSize = f->length();
    } else {
        mSize = size;
    }

    mapPtr = (byte *)mmap(nullptr,mSize,type,flag,fd,0);
    if(mapPtr == MAP_FAILED) {
        Trigger(InitializeException,"map file failed");
    }
}

_MappedFile::~_MappedFile() {
    if(mapPtr != nullptr) {
        munmap((void *)mapPtr, mSize);
        mapPtr = nullptr;
    }
}

void _MappedFile::sync() {
    msync((void *)mapPtr, mSize, MS_SYNC);
}

InputStream _MappedFile::getInputStream() {
    return createMappedFileInputStream(AutoClone(this));
}

OutputStream _MappedFile::getOutputStream() {
    return createMappedFileOutputStream(AutoClone(this));
}

long _MappedFile::size() {
    return mSize;
}

}