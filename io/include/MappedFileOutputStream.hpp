#ifndef __OBOTCHA_MAPPED_FILE_OUTPUT_STREAM_HPP__
#define __OBOTCHA_MAPPED_FILE_OUTPUT_STREAM_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ByteArray.hpp"
#include "OutputStream.hpp"
#include "MappedFile.hpp"

namespace obotcha {

DECLARE_CLASS(MappedFileOutputStream) IMPLEMENTS(OutputStream){

public:
    _MappedFileOutputStream(MappedFile);

    long write(char c);

    long write(ByteArray buff);

    long write(ByteArray buff,int start);

    long write(ByteArray buff,int start,int len);

    long writeString(String s);
    
    bool open(int opentype);

    bool open();
    
    void close();

    void flush();

    ~_MappedFileOutputStream();

private:
    MappedFile mFile;
};

}
#endif
