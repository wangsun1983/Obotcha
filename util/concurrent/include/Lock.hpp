#ifndef __OBOTCHA_LOCK_HPP__
#define __OBOTCHA_LOCK_HPP__

#include "Object.hpp"
#include "MethodNotSupportException.hpp"

namespace obotcha {

DECLARE_CLASS(Lock) {
  public:
    enum Type {
        Recursive = 0,
        Normal,
    };

    virtual int lock(long interval = 0) = 0;

    virtual int unlock() = 0;

    virtual bool isOwner() {
        Trigger(MethodNotSupportException,"Not Support")
    };
};

} // namespace obotcha
#endif