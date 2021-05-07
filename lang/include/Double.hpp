#ifndef __OBOTCHA_DOUBLE_HPP__
#define __OBOTCHA_DOUBLE_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

class _String;

DECLARE_SIMPLE_CLASS(Double)
{
public:
    _Double();
    
    _Double(double v);

    _Double(const Double &v);
    
    double toValue();

    void update(double);

    void update(const sp<_Double>&);

    bool equals(double p);
    
    bool equals(const Double &p);

    bool equals(const _Double *p);

    static sp<_String> className();

    uint64_t hashcode();

    ~_Double();

    static const double EPS;

private:
    double val;

};

}
#endif