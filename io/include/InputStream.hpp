#ifndef __INPUT_STREAM_HPP__
#define __INPUT_STREAM_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

DECLARE_SIMPLE_CLASS(InputStream) {
public:
    virtual int read();
    
    virtual int read(char *buffer,int size);

    virtual bool open();
    
    virtual void close();
};

#endif
