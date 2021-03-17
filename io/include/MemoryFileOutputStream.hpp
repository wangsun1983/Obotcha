#ifndef __OBOTCHA_MEMORY_FILE_OUTPUT_STREAM_HPP__
#define __OBOTCHA_MEMORY_FILE_OUTPUT_STREAM_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "File.hpp"
#include "ByteArray.hpp"
#include "OutputStream.hpp"
#include "MemoryFile.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(MemoryFileOutputStream) IMPLEMENTS(OutputStream){

public:

    _MemoryFileOutputStream(MemoryFile file);

    _MemoryFileOutputStream(String path);

    long write(char c);
    
    //bool write(char *buffer,int size);
    long write(ByteArray buff);

    long write(ByteArray buff,long size);

    long writeString(String s);
    
    bool open(long mapsize,FileOpenType opentype);

    bool open();
    
    void close();

    void flush();

    long getMemoryFileSize();

private:
    String mPath;

    //long filesize;

    char *mPtr;

    long mMapSize;

    FileOpenType mType;
};

}
#endif
