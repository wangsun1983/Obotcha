#ifndef __OUTPUT_STREAM_HPP__
#define __OUTPUT_STREAM_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

DECLARE_SIMPLE_CLASS(OutputStream) {
public:
    virtual bool write(char c);
    
    virtual bool write(char *buffer,int size);

    virtual bool open();
    
    virtual void close();

    virtual void flush();
};

#endif
