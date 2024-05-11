/**
 * @file LibraryFile.cpp
 * @brief A representation of memory-mapped file.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2024-01-03
 * @license none
 */
#include <fcntl.h>

#include "MappedFile.hpp"
#include "MappedFileInputStream.hpp"
#include "MappedFileOutputStream.hpp"
#include "Log.hpp"
#include "InitializeException.hpp"

namespace obotcha {

//-------- MappedFile --------
_MappedFile::_MappedFile(String path,uint64_t size,Flag flag) {
    File f = File::New(path);
    if(!f->exists()) {
        f->createNewFile();
    }

    int fd = ::open(f->getAbsolutePath()->toChars(),O_RDWR);

    if(f->length() == 0) {
        ftruncate(fd,size);
    }

    mSize = (size == 0)?f->length():size;

    mapPtr = (byte *)mmap(nullptr,
                          mSize,
                          PROT_READ|PROT_WRITE,
                          static_cast<int>(flag),fd,0);
    if(mapPtr == MAP_FAILED) {
        Trigger(InitializeException,"map file failed")
    }

    close(fd);
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
    return MappedFileInputStream::New(AutoClone(this));
}

OutputStream _MappedFile::getOutputStream() {
    return MappedFileOutputStream::New(AutoClone(this));
}

uint64_t _MappedFile::size() const {
    return mSize;
}

}
