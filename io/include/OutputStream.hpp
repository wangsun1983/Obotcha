#ifndef __OBOTCHA_OUTPUT_STREAM_HPP__
#define __OBOTCHA_OUTPUT_STREAM_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ByteArray.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(OutputStream) {
public:
    virtual long write(char c){return -1;}
    
    virtual long write(ByteArray buff,long size = -1){return -1;}

    virtual bool open(){return false;}

    virtual bool open(int){return false;}
    
    virtual void close(){}

    virtual void flush(){}

    enum FileOpenType {
        Append,
        Trunc
    };
};

}
#endif
