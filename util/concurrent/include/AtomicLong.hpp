#ifndef __OBOTCHA_ATOMIC_LONG_HPP__
#define __OBOTCHA_ATOMIC_LONG_HPP__

#include <atomic>

#include "Object.hpp"

namespace obotcha {

DECLARE_CLASS(AtomicLong) {
public:
    _AtomicLong(long val);
    long incrementAndGet();
    long decrementAndGet();
    long addAndGet(long val);
    long subAndGet(long val);
    long andAndGet(long val);
    long orAndGet(long val);
    long xorAndGet(long val);

    long getAndIncrement();
    long getAndDecrement();
    long getAndAdd(long val);
    long getAndSub(long val);
    long getAndAnd(long val);
    long getAndOr(long val);
    long getAndxor(long val);
    long getAndset(long val);

    void set(long val);
    long get();

private:
    std::atomic_long mValue;
};

} // namespace obotcha
#endif
