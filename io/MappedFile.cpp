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
    if(!f->exists()) {
        f->createNewFile();
    }

    int fd = -1;
    uint64_t flags = O_RDWR;

    if(type == PROT_READ) {
        flags = O_RDONLY;
    } else if(type == PROT_WRITE) {
        flags = O_WRONLY;
    }
    fd = ::open(f->getAbsolutePath()->toChars(),flags);

    if(f->length() == 0) {
        ftruncate(fd,size);
    }

    mSize = (size == 0)?f->length():size;
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
