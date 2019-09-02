#ifndef __FLOAT_HPP__
#define __FLOAT_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Float)
{
public:
    _Float(float v);

    _Float(Float v);

    float toValue();

    bool equals(Float p);

    bool equals(_Float *p);

    bool equals(float p);

    ~_Float();

    static const float EPS;

private:
    float val;

};

}
#endif