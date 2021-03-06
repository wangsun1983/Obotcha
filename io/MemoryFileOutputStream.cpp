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
    } else {
        mPath = nullptr;
    }
    mPtr = nullptr;
}

_MemoryFileOutputStream::_MemoryFileOutputStream(String path) {
    File f = createFile(path);
    mPath = f->getAbsolutePath();
    mPtr = nullptr;
}

long _MemoryFileOutputStream::write(char c) {
    if(mPtr == nullptr) {
        return false;
    }

    *mPtr = c;
    return 1;
}
    
long _MemoryFileOutputStream::write(ByteArray buff) {
    if(mPtr == nullptr||buff == nullptr) {
        return -1;
    }

    long length = buff->size()>mMapSize?mMapSize:buff->size();
    memcpy(mPtr,buff->toValue(),length);

    return length;
}

long _MemoryFileOutputStream::write(ByteArray buff,long size) {
    if(mPtr == nullptr || buff == nullptr) {
        return -1;
    }

    long length = buff->size() > size?size:buff->size();
    length = length > mMapSize?mMapSize:length;

    memcpy(mPtr,buff->toValue(),length);
    return length;
}

long _MemoryFileOutputStream::writeString(String s) {
    if(mPtr == nullptr || s == nullptr) {
        return -1;
    }

    long length = s->size()>mMapSize?mMapSize:s->size();
    memcpy(mPtr,s->toChars(),length);
    return length;
}
    
bool _MemoryFileOutputStream::open() {
    return open(MemoryFileOutPutDefaultSize,Trunc);
}

bool _MemoryFileOutputStream::open(long size,FileOpenType opentype) {
    mMapSize = size;
    FILE *fp = nullptr;

    switch(opentype) {
        case Append:{
            fp = fopen(mPath->toChars(), "a+");
            int fd = fileno(fp);
            struct stat statInfo;
            if(fstat(fd,&statInfo)!= 0) {
                return false;
            }
            
            if(ftruncate(fd, statInfo.st_size + mMapSize) != 0) {
                return false;
            }

            mPtr = (char *)mmap(NULL, statInfo.st_size + mMapSize, PROT_WRITE|PROT_READ, MAP_SHARED, fd, 0);
            mPtr += statInfo.st_size;
        }
        break;

        case Trunc:{
            fp = fopen(mPath->toChars(), "w+");
            int fd = fileno(fp);
            struct stat statInfo;
            if(fstat(fd,&statInfo)!= 0) {
                return false;
            }
    
            ftruncate(fd,mMapSize);
            mPtr = (char *)mmap(NULL, mMapSize, PROT_WRITE|PROT_READ, MAP_SHARED, fd, 0);
        }
            
        break;
    }

    if (fp == nullptr) {
        return false;
    }
      
    fclose(fp);

    if (mPtr == MAP_FAILED) {
        return false;
    }

    return true;
}
    
void _MemoryFileOutputStream::close() {
    if(mPtr != nullptr) {
        munmap(mPtr, mMapSize);
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

