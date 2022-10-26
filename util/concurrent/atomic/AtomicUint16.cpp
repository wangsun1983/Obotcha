#include "AtomicUint16.hpp"

namespace obotcha {

_AtomicUint16::_AtomicUint16(uint16_t val) { 
    mValue = val; 
}

uint16_t _AtomicUint16::incrementAndGet() { 
    return ++mValue; 
}

uint16_t _AtomicUint16::decrementAndGet() { 
    return --mValue; 
}

uint16_t _AtomicUint16::addAndGet(uint16_t val) {
    mValue += val;
    return mValue;
}

uint16_t _AtomicUint16::subAndGet(uint16_t val) {
    mValue -= val;
    return mValue;
}

uint16_t _AtomicUint16::andAndGet(uint16_t val) {
    mValue &= val;
    return mValue;
}

uint16_t _AtomicUint16::orAndGet(uint16_t val) {
    mValue |= val;
    return mValue;
}

uint16_t _AtomicUint16::xorAndGet(uint16_t val) {
    mValue |= ~val;
    return mValue;
}

uint16_t _AtomicUint16::getAndIncrement() { 
    return mValue++; 
}

uint16_t _AtomicUint16::getAndDecrement() { 
    return mValue--; 
}

uint16_t _AtomicUint16::getAndAdd(uint16_t val) {
    return mValue.fetch_add(val);
}

uint16_t _AtomicUint16::getAndSub(uint16_t val) {
    return mValue.fetch_sub(val);
}

uint16_t _AtomicUint16::getAndAnd(uint16_t val) {
    return mValue.fetch_and(val);
}

uint16_t _AtomicUint16::getAndOr(uint16_t val) { 
    return mValue.fetch_or(val); 
}

uint16_t _AtomicUint16::getAndxor(uint16_t val) {
    return mValue.fetch_or(~val);
}

void _AtomicUint16::set(uint16_t val) { 
    mValue = val; 
}

uint16_t _AtomicUint16::get() { 
    return mValue; 
}

} // namespace obotcha