#ifndef __OBOTCHA_INPUT_STREAM_HPP__
#define __OBOTCHA_INPUT_STREAM_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ByteArray.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(InputStream) {
public:
    virtual long read(ByteArray){return -1;} //return size;

    virtual bool open() {return false;}
    
    virtual void close() {}
};

}
#endif
