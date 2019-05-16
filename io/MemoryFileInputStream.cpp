#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "File.hpp"
#include "ByteArray.hpp"
#include "MemoryFileInputStream.hpp"

namespace obotcha {

_MemoryFileInputStream::_MemoryFileInputStream(MemoryFile f) {
    mPath = createString(f->getAbsolutePath());
    filesize = f->length();
}
    
_MemoryFileInputStream::_MemoryFileInputStream(String path) {
    File f = createFile(path);
    mPath = f->getAbsolutePath();
    filesize = f->length();
}

int _MemoryFileInputStream::read() {
    //TODO
    return 0;
}

int _MemoryFileInputStream::read(ByteArray buffer) {
    long size = buffer->size() > filesize?filesize:buffer->size();

    memcpy(buffer->toValue(),mPtr,size);
}

int _MemoryFileInputStream::read(int index,ByteArray buffer) {

    long size = buffer->size() > (filesize-index)?(filesize -index):buffer->size();

    memcpy(buffer->toValue(),(mPtr+index),size);
}

ByteArray _MemoryFileInputStream::readAll() {
    return createByteArray(mPtr,filesize);
}

bool _MemoryFileInputStream::open() {

    FILE *fp = fopen(mPath->toChars(), "rb");
    if (fp == nullptr) {
        return false;
    }

    int fd = fileno(fp);
 
    mPtr = (char *)mmap(NULL, filesize, PROT_READ, MAP_SHARED, fd, 0);
    if (mPtr == MAP_FAILED) {
        return false;
    }

    fclose(fp);
    return true;
}

void _MemoryFileInputStream::close() {
    munmap(mPtr, filesize);
}

}
