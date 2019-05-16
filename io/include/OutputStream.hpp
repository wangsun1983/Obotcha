#ifndef __OUTPUT_STREAM_HPP__
#define __OUTPUT_STREAM_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ByteArray.hpp"

namespace obotcha {

enum FileOpenType {
    Append,
    Trunc
};

DECLARE_SIMPLE_CLASS(OutputStream) {
public:
    virtual bool write(char c);
    
    virtual bool write(ByteArray);

    virtual bool write(ByteArray buff,long size);

    virtual bool open();

    virtual bool open(FileOpenType);
    
    virtual void close();

    virtual void flush();
};

}
#endif
