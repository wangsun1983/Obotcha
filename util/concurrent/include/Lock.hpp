#ifndef __OBOTCHA_LOCK_HPP__
#define __OBOTCHA_LOCK_HPP__

#include "Object.hpp"
#include "MethodNotSupportException.hpp"
#include "Concurrent.hpp"

namespace obotcha {

DECLARE_CLASS(Lock) {
  public:
    enum class Type {
        Recursive = 0,
        Normal,
    };

    virtual int lock(long interval = st(Concurrent)::kWaitForEver) = 0;

    virtual int unlock() = 0;

    virtual bool isOwner() {
        Trigger(MethodNotSupportException,"Not Support")
    };
};

} // namespace obotcha
#endif