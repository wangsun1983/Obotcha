#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>


#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "File.hpp"
#include "ByteArray.hpp"
#include "MemoryFileOutputStream.hpp"

namespace obotcha {

#define MemoryFileOutPutDefaultSize 4096

_MemoryFileOutputStream::_MemoryFileOutputStream(MemoryFile file) {
    mPath = createString(file->getAbsolutePath());
    filesize = file->length();
}

_MemoryFileOutputStream::_MemoryFileOutputStream(String path) {
    File f = createFile(path);
    mPath = f->getAbsolutePath();
    filesize = f->length();
}

bool _MemoryFileOutputStream::write(char c) {

}
    
bool _MemoryFileOutputStream::write(ByteArray buff) {
    memcpy(mPtr,buff->toValue(),buff->size());
}

bool _MemoryFileOutputStream::write(ByteArray buff,long size) {
    //TODO
}

bool _MemoryFileOutputStream::writeString(String s) {
    memcpy(mPtr,s->toChars(),s->size());
}
    
bool _MemoryFileOutputStream::open(FileOpenType opentype) {
    return open();
}

bool _MemoryFileOutputStream::open() {
    return open(MemoryFileOutPutDefaultSize);
}

bool _MemoryFileOutputStream::open(long size) {
    printf("memory123 file open start,size is %d \n",size);

    mMapSize = size;
    printf("memory123 file open start,mMapSize is %d \n",mMapSize);

    FILE *fp = fopen(mPath->toChars(), "a+");
    if (fp == nullptr) {
        return false;
    }

    int fd = fileno(fp);
    printf("filesize is %d,fd is %d \n",filesize,fd);

    mPtr = (char *)mmap(NULL, mMapSize, PROT_WRITE, MAP_SHARED, fd, 0);
    printf("mPtr is %lx \n",mPtr);    

    if (mPtr == MAP_FAILED) {
        printf("map failed reason is %s \n",strerror(errno));
        return false;
    }

    fclose(fp);

    return true;
}
    
void _MemoryFileOutputStream::close() {
    munmap(mPtr, filesize);
}

void _MemoryFileOutputStream::flush() {

}

}

