#ifndef __MEMORY_FILE_OUTPUT_STREAM_HPP__
#define __MEMORY_FILE_OUTPUT_STREAM_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "File.hpp"
#include "ByteArray.hpp"
#include "OutputStream.hpp"
#include "MemoryFile.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(MemoryFileOutputStream) EXTENDS(OutputStream){

public:

    _MemoryFileOutputStream(MemoryFile file);

    _MemoryFileOutputStream(String path);

    bool write(char c);
    
    //bool write(char *buffer,int size);
    bool write(ByteArray buff);

    bool write(ByteArray buff,long size);

    bool writeString(String s);
    
    //no use
    bool open(FileOpenType opentype);

    bool open(long mapsize);

    bool open();
    
    void close();

    void flush();

private:
    String mPath;

    long filesize;

    char *mPtr;

    long mMapSize;
};

}
#endif
