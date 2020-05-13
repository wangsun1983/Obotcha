#ifndef __OBOTCHA_ATOMIC_UINT64_HPP__
#define __OBOTCHA_ATOMIC_UINT64_HPP__

#include <pthread.h>
#include <sys/time.h>
#include <atomic>

#include "Mutex.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(AtomicUint64) {

public:
    _AtomicUint64(uint64_t val);
    uint64_t incrementAndGet();
    uint64_t decrementAndGet();
    uint64_t addAndGet(uint64_t val);
    uint64_t subAndGet(uint64_t val);
    uint64_t andAndGet(uint64_t val);
    uint64_t orAndGet(uint64_t val);
    uint64_t xorAndGet(uint64_t val);
    
    uint64_t getAndIncrement();
    uint64_t getAndDecrement();
    uint64_t getAndAdd(uint64_t val);
    uint64_t getAndSub(uint64_t val);
    uint64_t getAndAnd(uint64_t val);
    uint64_t getAndOr(uint64_t val);
    uint64_t getAndxor(uint64_t val);
    uint64_t getAndset(uint64_t val);

    void set(uint64_t val);
    uint64_t get();
   
private:
    std::atomic_ullong mValue;
};

}
#endif