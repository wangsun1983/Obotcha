#include "AtomicUint64.hpp"

namespace obotcha {

_AtomicUint64::_AtomicUint64(uint64_t val) { 
    mValue = val; 
}

uint64_t _AtomicUint64::incrementAndGet() { 
    return ++mValue; 
}

uint64_t _AtomicUint64::decrementAndGet() { 
    return --mValue; 
}

uint64_t _AtomicUint64::addAndGet(uint64_t val) {
    mValue += val;
    return mValue;
}

uint64_t _AtomicUint64::subAndGet(uint64_t val) {
    mValue -= val;
    return mValue;
}

uint64_t _AtomicUint64::andAndGet(uint64_t val) {
    mValue &= val;
    return mValue;
}

uint64_t _AtomicUint64::orAndGet(uint64_t val) {
    mValue |= val;
    return mValue;
}

uint64_t _AtomicUint64::xorAndGet(uint64_t val) {
    mValue |= ~val;
    return mValue;
}

uint64_t _AtomicUint64::getAndIncrement() { 
    return mValue++; 
}

uint64_t _AtomicUint64::getAndDecrement() { 
    return mValue--; 
}

uint64_t _AtomicUint64::getAndAdd(uint64_t val) {
    return mValue.fetch_add(val);
}

uint64_t _AtomicUint64::getAndSub(uint64_t val) {
    return mValue.fetch_sub(val);
}

uint64_t _AtomicUint64::getAndAnd(uint64_t val) {
    return mValue.fetch_and(val);
}

uint64_t _AtomicUint64::getAndOr(uint64_t val) { 
    return mValue.fetch_or(val); 
}

uint64_t _AtomicUint64::getAndxor(uint64_t val) {
    return mValue.fetch_or(~val);
}

void _AtomicUint64::set(uint64_t val) { 
    mValue = val; 
}

uint64_t _AtomicUint64::get() { 
    return mValue; 
}

} // namespace obotcha