#include "AtomicLong.hpp"

namespace obotcha {

_AtomicLong::_AtomicLong(long val) { 
    mValue = val; 
}

long _AtomicLong::incrementAndGet() { 
    return ++mValue; 
}

long _AtomicLong::decrementAndGet() { 
    return --mValue; 
}

long _AtomicLong::addAndGet(long val) {
    mValue += val;
    return mValue;
}

long _AtomicLong::subAndGet(long val) {
    mValue -= val;
    return mValue;
}

long _AtomicLong::andAndGet(long val) {
    mValue &= val;
    return mValue;
}

long _AtomicLong::orAndGet(long val) {
    mValue |= val;
    return mValue;
}

long _AtomicLong::xorAndGet(long val) {
    mValue |= ~val;
    return mValue;
}

long _AtomicLong::getAndIncrement() { 
    return mValue++; 
}

long _AtomicLong::getAndDecrement() { 
    return mValue--; 
}

long _AtomicLong::getAndAdd(long val) { 
    return mValue.fetch_add(val); 
}

long _AtomicLong::getAndSub(long val) { 
    return mValue.fetch_sub(val); 
}

long _AtomicLong::getAndAnd(long val) { 
    return mValue.fetch_and(val); 
}

long _AtomicLong::getAndOr(long val) { 
    return mValue.fetch_or(val); 
}

long _AtomicLong::getAndxor(long val) { 
    return mValue.fetch_or(~val); 
}

void _AtomicLong::set(long val) { 
    mValue = val; 
}

long _AtomicLong::get() { 
    return mValue; 
}

} // namespace obotcha