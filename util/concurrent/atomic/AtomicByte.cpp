#include "AtomicByte.hpp"

namespace obotcha {

_AtomicByte::_AtomicByte(byte val) { mValue = val; }

byte _AtomicByte::incrementAndGet() { return ++mValue; }

byte _AtomicByte::decrementAndGet() { return --mValue; }

byte _AtomicByte::addAndGet(byte val) {
    mValue += val;
    return mValue;
}

byte _AtomicByte::subAndGet(byte val) {
    mValue -= val;
    return mValue;
}

byte _AtomicByte::andAndGet(byte val) {
    mValue &= val;
    return mValue;
}

byte _AtomicByte::orAndGet(byte val) {
    mValue |= val;
    return mValue;
}

byte _AtomicByte::xorAndGet(byte val) {
    mValue |= ~val;
    return mValue;
}

byte _AtomicByte::getAndIncrement() {
    return mValue++; 
}

byte _AtomicByte::getAndDecrement() { return mValue--; }

byte _AtomicByte::getAndAdd(byte val) { return mValue.fetch_add(val); }

byte _AtomicByte::getAndSub(byte val) { return mValue.fetch_sub(val); }

byte _AtomicByte::getAndAnd(byte val) { return mValue.fetch_and(val); }

byte _AtomicByte::getAndOr(byte val) { return mValue.fetch_or(val); }

byte _AtomicByte::getAndxor(byte val) { return mValue.fetch_or(~val); }

void _AtomicByte::set(byte val) { mValue = val; }

byte _AtomicByte::get() { return mValue; }

} // namespace obotcha
