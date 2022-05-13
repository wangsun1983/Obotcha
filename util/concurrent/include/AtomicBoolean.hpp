#ifndef __OBOTCHA_ATOMIC_BOOLEANR_HPP__
#define __OBOTCHA_ATOMIC_BOOLEANR_HPP__

#include <atomic>

#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

DECLARE_CLASS(AtomicBoolean) {

  public:
    _AtomicBoolean(bool val);

    void set(bool val);
    bool get();

  private:
    std::atomic_bool mValue;
};

} // namespace obotcha
#endif
