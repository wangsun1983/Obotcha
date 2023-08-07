#ifndef __OBOTCHA_ATOMIC_UINT32_HPP__
#define __OBOTCHA_ATOMIC_UINT32_HPP__

#include <atomic>

#include "Object.hpp"

namespace obotcha {

DECLARE_CLASS(AtomicUint32) {

  public:
    explicit _AtomicUint32(uint32_t val);
    uint32_t incrementAndGet();
    uint32_t decrementAndGet();
    uint32_t addAndGet(uint32_t val);
    uint32_t subAndGet(uint32_t val);
    uint32_t andAndGet(uint32_t val);
    uint32_t orAndGet(uint32_t val);
    uint32_t xorAndGet(uint32_t val);

    uint32_t getAndIncrement();
    uint32_t getAndDecrement();
    uint32_t getAndAdd(uint32_t val);
    uint32_t getAndSub(uint32_t val);
    uint32_t getAndAnd(uint32_t val);
    uint32_t getAndOr(uint32_t val);
    uint32_t getAndxor(uint32_t val);
    uint32_t getAndset(uint32_t val);

    void set(uint32_t val);
    uint32_t get() const;

  private:
    std::atomic<uint32_t> mValue;
};

} // namespace obotcha
#endif
