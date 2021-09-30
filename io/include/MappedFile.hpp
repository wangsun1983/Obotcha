#ifndef __OBOTCHA_MAPPED_FILE_HPP__
#define __OBOTCHA_MAPPED_FILE_HPP__

#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ArrayList.hpp"
#include "File.hpp"
#include "String.hpp"
#include "ByteArray.hpp"

namespace obotcha {

class _MappedFile;

DECLARE_CLASS(MappedFileBuilder) {
public:
    _MappedFileBuilder(String);
    _MappedFileBuilder(const char *);

    _MappedFileBuilder* setSize(int);
    _MappedFileBuilder* setProtType(int);
    _MappedFileBuilder* setMapFlag(int);
    
    sp<_MappedFile> create();
private:
    String path;
    int size;
    int protType;
    int mapFlag;
};

DECLARE_CLASS(MappedFile) {
public:
    friend class _MappedFileBuilder;
    enum Prot{
      Read = PROT_READ,
      Write = PROT_WRITE 
    };

    enum Flag {
      Shared = MAP_SHARED,
      Private = MAP_PRIVATE
    };

    _MappedFile();
    void close();
    void sync();
    ByteArray getData();

private:
    ByteArray mdata;
    void *mapPtr;
    int size;
};

} // namespace obotcha
#endif
