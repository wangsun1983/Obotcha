#ifndef __OBOTCHA_LOCK_HPP__
#define __OBOTCHA_LOCK_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

DECLARE_CLASS(Lock) {
  public:
    enum Type {
        Recursive = 0,
        Normal,
    };

    virtual int lock() = 0;

    virtual int unlock() = 0;

protected:
    int convertResult(int);  
};

} // namespace obotcha
#endif