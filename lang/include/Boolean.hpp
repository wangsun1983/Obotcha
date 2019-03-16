#ifndef __BOOLEAN_HPP__
#define __BOOLEAN_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Boolean) {
public:
    _Boolean(bool v);

    _Boolean(Boolean v);

    bool toValue();

    bool equals(Boolean p);

    bool equals(bool p);

    ~_Boolean();

private:
    bool val;

};

}

#endif
