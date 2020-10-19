#ifndef __OBOTCHA_LOCK_HPP__
#define __OBOTCHA_LOCK_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Lock) {
public:
    virtual int lock() = 0;

    virtual int unlock() = 0;
};

}
#endif