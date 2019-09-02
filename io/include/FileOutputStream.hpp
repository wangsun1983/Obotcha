#ifndef __FILE_OUTPUT_STREAM_HPP__
#define __FILE_OUTPUT_STREAM_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "File.hpp"
#include "ByteArray.hpp"
#include "OutputStream.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(FileOutputStream) EXTENDS(OutputStream){

public:

    _FileOutputStream(File file);

    _FileOutputStream(String path);

    _FileOutputStream(const char *);

    bool write(char c);
    
    //bool write(char *buffer,int size);
    long write(ByteArray buff);

    long write(ByteArray buff,long size);

    bool writeString(String s);
    
    bool open(FileOpenType opentype);

    bool open();
    
    void close();

    void flush();

private:
    String mPath;

    std::ofstream fstream;
};

}
#endif
