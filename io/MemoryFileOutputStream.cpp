#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "File.hpp"
#include "ByteArray.hpp"
#include "MemoryFileOutputStream.hpp"

namespace obotcha {

#define MemoryFileOutPutDefaultSize 4096

_MemoryFileOutputStream::_MemoryFileOutputStream(MemoryFile file) {
    if(file != nullptr) {
        mPath = createString(file->getAbsolutePath());
        filesize = file->length();
    } else {
        mPath = nullptr;
        filesize = 0;
    }

    mPtr = nullptr;
}

_MemoryFileOutputStream::_MemoryFileOutputStream(String path) {
    File f = createFile(path);
    mPath = f->getAbsolutePath();
    filesize = f->length();
    mPtr = nullptr;
}

bool _MemoryFileOutputStream::write(char c) {
    if(mPtr == nullptr) {
        return false;
    }

    *mPtr = c;
    return true;
}
    
long _MemoryFileOutputStream::write(ByteArray buff) {
    if(mPtr == nullptr) {
        return -1;
    }

    long length = buff->size()>mMapSize?mMapSize:buff->size();
    memcpy(mPtr,buff->toValue(),length);

    return length;
}

long _MemoryFileOutputStream::write(ByteArray buff,long size) {
    if(mPtr == nullptr) {
        return -1;
    }

    long length = buff->size() > size?size:buff->size();
    length = length > mMapSize?mMapSize:length;

    memcpy(mPtr,buff->toValue(),length);
    return length;
}

bool _MemoryFileOutputStream::writeString(String s) {
    if(mPtr == nullptr) {
        return false;
    }

    long length = s->size()>mMapSize?mMapSize:s->size();
    memcpy(mPtr,s->toChars(),length);
    return true;
}
    
bool _MemoryFileOutputStream::open(FileOpenType opentype) {
    return open();
}

bool _MemoryFileOutputStream::open() {
    return open(MemoryFileOutPutDefaultSize);
}

bool _MemoryFileOutputStream::open(long size,FileOpenType opentype) {
    mMapSize = size;
    FILE *fp = nullptr;
    switch(opentype) {
        case Append:
            fp = fopen(mPath->toChars(), "a+");
        break;

        case Trunc:
            fp = fopen(mPath->toChars(), "w+");
        break;
    }

    if (fp == nullptr) {
        return false;
    }

    int fd = fileno(fp);
    printf("mMapSize is %ld,fd is %d \n",mMapSize,fd);
    // solve the bus error problem:
    // we should allocate space for the file first.
    fseek(fp, mMapSize, SEEK_SET);
    fwrite("",1,1,fp);

    mPtr = (char *)mmap(NULL, mMapSize, PROT_WRITE|PROT_READ, MAP_SHARED, fd, 0);
    //printf("mPtr is %x \n",mPtr);    
    fclose(fp);

    if (mPtr == MAP_FAILED) {
        printf("map failed reason is %s \n",strerror(errno));
        return false;
    }

    return true;
}
    
void _MemoryFileOutputStream::close() {
    if(mPtr != nullptr) {
        munmap(mPtr, filesize);
    }
}

void _MemoryFileOutputStream::flush() {
    if(mPtr != nullptr) {
        msync(mPtr,mMapSize,MS_ASYNC);
    }
}

long _MemoryFileOutputStream::getMemoryFileSize() {
    return mMapSize;
}

}

