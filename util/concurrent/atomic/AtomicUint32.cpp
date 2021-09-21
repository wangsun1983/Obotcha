#include "AtomicUint32.hpp"

namespace obotcha {

_AtomicUint32::_AtomicUint32(uint32_t val) { mValue = val; }

uint32_t _AtomicUint32::incrementAndGet() { return ++mValue; }

uint32_t _AtomicUint32::decrementAndGet() { return --mValue; }

uint32_t _AtomicUint32::addAndGet(uint32_t val) {
    mValue += val;
    return mValue;
}

uint32_t _AtomicUint32::subAndGet(uint32_t val) {
    mValue -= val;
    return mValue;
}

uint32_t _AtomicUint32::andAndGet(uint32_t val) {
    mValue &= val;
    return mValue;
}

uint32_t _AtomicUint32::orAndGet(uint32_t val) {
    mValue |= val;
    return mValue;
}

uint32_t _AtomicUint32::xorAndGet(uint32_t val) {
    mValue |= ~val;
    return mValue;
}

uint32_t _AtomicUint32::getAndIncrement() { return mValue++; }

uint32_t _AtomicUint32::getAndDecrement() { return mValue--; }

uint32_t _AtomicUint32::getAndAdd(uint32_t val) {
    return mValue.fetch_add(val);
}

uint32_t _AtomicUint32::getAndSub(uint32_t val) {
    return mValue.fetch_sub(val);
}

uint32_t _AtomicUint32::getAndAnd(uint32_t val) {
    return mValue.fetch_and(val);
}

uint32_t _AtomicUint32::getAndOr(uint32_t val) { return mValue.fetch_or(val); }

uint32_t _AtomicUint32::getAndxor(uint32_t val) {
    return mValue.fetch_or(~val);
}

void _AtomicUint32::set(uint32_t val) { mValue = val; }

uint32_t _AtomicUint32::get() { return mValue; }

} // namespace obotcha