#ifndef __OBOTCHA_INPUT_STREAM_HPP__
#define __OBOTCHA_INPUT_STREAM_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ByteArray.hpp"

namespace obotcha {

DECLARE_CLASS(InputStream) {
public:
    virtual long read(ByteArray) = 0; //return size;

    virtual long read(ByteArray,int start) = 0;

    virtual bool open() {return false;}
    
    virtual void close() {}
};

}
#endif
