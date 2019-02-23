#ifndef __FLOAT_HPP__
#define __FLOAT_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

DECLARE_SIMPLE_CLASS(Float)
{
public:
    _Float(float v);

    _Float(Float v);

    float toValue();

    bool equals(Float p);

    bool equals(float p);

    ~_Float();

private:
    float val;

};

#endif