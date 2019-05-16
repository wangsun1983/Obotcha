#ifndef __INPUT_STREAM_HPP__
#define __INPUT_STREAM_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ByteArray.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(InputStream) {
public:
    virtual int read();
    
    virtual int read(ByteArray);

    virtual bool open();
    
    virtual void close();
};

}
#endif
