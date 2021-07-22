#ifndef __OBOTCHA_FLOAT_HPP__
#define __OBOTCHA_FLOAT_HPP__

#include "Object.hpp"

namespace obotcha {

class _String;

DECLARE_SIMPLE_CLASS(Float) {
public:
    static const int __isReflected = 1;

    _Float();
    
    _Float(float v);

    _Float(Float &v);

    float toValue();

    bool equals(Float &p);

    bool equals(const _Float *p);

    bool equals(float p);

    void update(float v);

    void update(sp<_Float> v);

    static bool isEqual(float,float);

    static sp<_Float> parse(sp<_String>);

    static sp<_String> className();

    uint64_t hashcode();

    sp<_String> toString();

    ~_Float();

private:
    float val;

};

}
#endif