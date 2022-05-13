#ifndef __OBOTCHA_ATOMIC_UINT16_HPP__
#define __OBOTCHA_ATOMIC_UINT16_HPP__

#include <atomic>

#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

DECLARE_CLASS(AtomicUint16) {

  public:
    _AtomicUint16(uint16_t val);
    uint16_t incrementAndGet();
    uint16_t decrementAndGet();
    uint16_t addAndGet(uint16_t val);
    uint16_t subAndGet(uint16_t val);
    uint16_t andAndGet(uint16_t val);
    uint16_t orAndGet(uint16_t val);
    uint16_t xorAndGet(uint16_t val);

    uint16_t getAndIncrement();
    uint16_t getAndDecrement();
    uint16_t getAndAdd(uint16_t val);
    uint16_t getAndSub(uint16_t val);
    uint16_t getAndAnd(uint16_t val);
    uint16_t getAndOr(uint16_t val);
    uint16_t getAndxor(uint16_t val);
    uint16_t getAndset(uint16_t val);

    void set(uint16_t val);
    uint16_t get();

  private:
    std::atomic<uint16_t> mValue;
};

} // namespace obotcha
#endif
