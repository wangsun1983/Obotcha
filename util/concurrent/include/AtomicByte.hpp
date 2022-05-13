#ifndef __OBOTCHA_ATOMIC_BYTE_HPP__
#define __OBOTCHA_ATOMIC_BYTE_HPP__

#include <atomic>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Byte.hpp"

namespace obotcha {

DECLARE_CLASS(AtomicByte) {

  public:
    _AtomicByte(uint8_t val);
    uint8_t incrementAndGet();
    uint8_t decrementAndGet();
    uint8_t addAndGet(uint8_t val);
    uint8_t subAndGet(uint8_t val);
    uint8_t andAndGet(uint8_t val);
    uint8_t orAndGet(uint8_t val);
    uint8_t xorAndGet(uint8_t val);

    uint8_t getAndIncrement();
    uint8_t getAndDecrement();
    uint8_t getAndAdd(uint8_t val);
    uint8_t getAndSub(uint8_t val);
    uint8_t getAndAnd(uint8_t val);
    uint8_t getAndOr(uint8_t val);
    uint8_t getAndxor(uint8_t val);
    uint8_t getAndset(uint8_t val);

    void set(uint8_t val);
    uint8_t get();

  private:
    std::atomic<uint8_t> mValue;
};

} // namespace obotcha
#endif
