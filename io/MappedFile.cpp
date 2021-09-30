#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "MappedFile.hpp"

namespace obotcha {

//-------- MappedFileBuilder --------
_MappedFileBuilder::_MappedFileBuilder(String p) {
    path = p;
    protType = PROT_READ|PROT_WRITE;
    mapFlag = MAP_SHARED;
}

_MappedFileBuilder::_MappedFileBuilder(const char *p):_MappedFileBuilder(createString(p)) {

}

_MappedFileBuilder* _MappedFileBuilder::setSize(int s) {
    size = s;
    return this;
}

_MappedFileBuilder* _MappedFileBuilder::setProtType(int t) {
    protType = t;
    return this;
}

_MappedFileBuilder* _MappedFileBuilder::setMapFlag(int t) {
    mapFlag = t;
    return this;
}

MappedFile _MappedFileBuilder::create() {
    File f = createFile(path);
    if(!f->exists()) {
      return nullptr;
    }

    int fd = open(f->getAbsolutePath()->toChars(),O_RDWR);
    void *ptr = mmap(nullptr,size,protType,mapFlag,fd,0);
    if(ptr != nullptr) {
      MappedFile file = createMappedFile();
      file->size = size;
      file->mapPtr = ptr;
      file->mdata = createByteArray((const byte *)ptr,size,true);
      return file;
    }

    return nullptr;
}

//-------- MappedFile --------
void _MappedFile::close() {
    if(mapPtr != nullptr) {
        munmap((void *)mapPtr, size);
        mapPtr = nullptr;
    }
}

void _MappedFile::sync() {
    msync((void *)mapPtr, size, MS_SYNC);
}

ByteArray _MappedFile::getData() {
    return mdata;
}

_MappedFile::_MappedFile() {
    mapPtr = nullptr;
}

}