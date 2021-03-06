#ifndef __OBOTCHA_FILE_OUTPUT_STREAM_HPP__
#define __OBOTCHA_FILE_OUTPUT_STREAM_HPP__

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

    long write(char c);
    
    long write(ByteArray buff);

    long write(ByteArray buff,long size);

    bool writeString(String s);
    
    bool open(int opentype);

    bool open();
    
    void close();

    void flush();

    ~_FileOutputStream();

private:
    String mPath;

    std::ofstream fstream;
};

}
#endif
