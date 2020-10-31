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
#include "FileNotFoundException.hpp"
#include "MethodNotSupportException.hpp"

namespace obotcha {

_MemoryFileInputStream::_MemoryFileInputStream(MemoryFile f):_MemoryFileInputStream(f->getAbsolutePath()) {
    
}
    
_MemoryFileInputStream::_MemoryFileInputStream(String path) {
    File f = createFile(path);
    if(!f->exists()) {
        Trigger(FileNotFoundException,"file not exists");
    }

    mPath = f->getAbsolutePath();
    filesize = f->length();

    mPtr = nullptr;
}

int _MemoryFileInputStream::read() {
    Trigger(MethodNotSupportException,"MemoryFileInputStream do not support read");
}

long _MemoryFileInputStream::read(ByteArray buffer) {
    if(mPtr == nullptr || buffer == nullptr) {
        return -1;
    }

    long size = buffer->size() > filesize?filesize:buffer->size();

    memcpy(buffer->toValue(),mPtr,size);

    return size;
}

long _MemoryFileInputStream::read(int index,ByteArray buffer) {
    if(mPtr == nullptr || buffer == nullptr || index >= filesize) {
        return -1;
    }

    long size = buffer->size() > (filesize-index)?(filesize -index):buffer->size();

    memcpy(buffer->toValue(),(mPtr+index),size);

    return size;
}

ByteArray _MemoryFileInputStream::readAll() {
    if(mPtr == nullptr) {
        return nullptr;
    }

    return createByteArray(mPtr,filesize);
}

bool _MemoryFileInputStream::open() {

    FILE *fp = fopen(mPath->toChars(), "rb");
    if (fp == nullptr) {
        return false;
    }

    int fd = fileno(fp);
 
    mPtr = (unsigned char *)mmap(NULL, filesize, PROT_READ, MAP_SHARED, fd, 0);
    if (mPtr == MAP_FAILED) {
        mPtr == nullptr;
        return false;
    }

    fclose(fp);
    return true;
}

void _MemoryFileInputStream::close() {
    if(mPtr == nullptr) {
        return;
    }
    
    munmap(mPtr, filesize);
    mPtr = nullptr;
}

_MemoryFileInputStream::~_MemoryFileInputStream() {
    if(mPtr != nullptr) {
        close();
    }
}

}
