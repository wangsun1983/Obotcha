#ifndef __OBOTCHA_ATOMIC_INTEGER_HPP__
#define __OBOTCHA_ATOMIC_INTEGER_HPP__

#include "Object.hpp"

namespace obotcha {

DECLARE_CLASS(AtomicInteger) {
public:
    _AtomicInteger();
    explicit _AtomicInteger(int val);
    int incrementAndGet();
    int decrementAndGet();
    int addAndGet(int val);
    int subAndGet(int val);
    int andAndGet(int val);
    int orAndGet(int val);
    int xorAndGet(int val);

    int getAndIncrement();
    int getAndDecrement();
    int getAndAdd(int val);
    int getAndSub(int val);
    int getAndAnd(int val);
    int getAndOr(int val);
    int getAndxor(int val);
    int compareAndSet(int val);

    void set(int val);
    int get();

private:
    mutable volatile int value;
};

} // namespace obotcha
#endif
