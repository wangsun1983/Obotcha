#ifndef __OBOTCHA_DOUBLE_HPP__
#define __OBOTCHA_DOUBLE_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Double)
{
public:
    _Double(double v);

    _Double(Double &v);
    
    double toValue();

    void update(double);

    void update(sp<_Double>);

    bool equals(double p);
    
    bool equals(Double &p);

    bool equals(const _Double *p);

    ~_Double();

    static const double EPS;

private:
    double val;

};

}
#endif