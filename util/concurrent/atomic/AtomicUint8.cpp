#include "AtomicUint8.hpp"

namespace obotcha {

_AtomicUint8::_AtomicUint8(uint8_t val) { 
    mValue = val; 
}

uint8_t _AtomicUint8::incrementAndGet() { 
    return ++mValue; 
}

uint8_t _AtomicUint8::decrementAndGet() { 
    return --mValue; 
}

uint8_t _AtomicUint8::addAndGet(uint8_t val) {
    mValue += val;
    return mValue;
}

uint8_t _AtomicUint8::subAndGet(uint8_t val) {
    mValue -= val;
    return mValue;
}

uint8_t _AtomicUint8::andAndGet(uint8_t val) {
    mValue &= val;
    return mValue;
}

uint8_t _AtomicUint8::orAndGet(uint8_t val) {
    mValue |= val;
    return mValue;
}

uint8_t _AtomicUint8::xorAndGet(uint8_t val) {
    mValue |= ~val;
    return mValue;
}

uint8_t _AtomicUint8::getAndIncrement() { 
    return mValue++; 
}

uint8_t _AtomicUint8::getAndDecrement() { 
    return mValue--; 
}

uint8_t _AtomicUint8::getAndAdd(uint8_t val) {
    return mValue.fetch_add(val);
}

uint8_t _AtomicUint8::getAndSub(uint8_t val) {
    return mValue.fetch_sub(val);
}

uint8_t _AtomicUint8::getAndAnd(uint8_t val) {
    return mValue.fetch_and(val);
}

uint8_t _AtomicUint8::getAndOr(uint8_t val) { 
    return mValue.fetch_or(val); 
}

uint8_t _AtomicUint8::getAndxor(uint8_t val) {
    return mValue.fetch_or(~val);
}

void _AtomicUint8::set(uint8_t val) { 
    mValue = val; 
}

uint8_t _AtomicUint8::get() { 
    return mValue; 
}

} // namespace obotcha