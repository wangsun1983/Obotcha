#include "AtomicUint64.hpp"

namespace obotcha {

_AtomicUint64::_AtomicUint64(uint64_t val) {
    mValue = val;
}

uint64_t _AtomicUint64::incrementAndGet() {
    //return __sync_add_and_fetch(&value,1);
    return ++mValue;
}

uint64_t _AtomicUint64::decrementAndGet() {
    //return __sync_add_and_fetch(&value,-1);
    return --mValue;
}

uint64_t _AtomicUint64::addAndGet(uint64_t val) {
    //return __sync_add_and_fetch(&value,val);
    mValue+= val;
    return mValue;
}

uint64_t _AtomicUint64::subAndGet(uint64_t val) {
    //return __sync_sub_and_fetch(&value,val);
    mValue -= val;
    return mValue;
}

uint64_t _AtomicUint64::andAndGet(uint64_t val) {
    //return __sync_and_and_fetch(&value,val);
    mValue &= val;
    return mValue;
}

uint64_t _AtomicUint64::orAndGet(uint64_t val) {
    //return __sync_or_and_fetch(&value,val);
    mValue |= val;
    return mValue;
}

uint64_t _AtomicUint64::xorAndGet(uint64_t val) {
    //return __sync_xor_and_fetch(&value,val);
    mValue |= ~val;
    return mValue;
}

uint64_t _AtomicUint64::getAndIncrement() {
    //return __sync_fetch_and_add(&value,1);
    return mValue++;
}

uint64_t _AtomicUint64::getAndDecrement() {
    //return __sync_fetch_and_add(&value,-1);
    return mValue--;
}

uint64_t _AtomicUint64::getAndAdd(uint64_t val) {
    //return __sync_fetch_and_add(&value,val);
    //long v = mValue;
    //mValue += val;
    return mValue.fetch_add(val);
}

uint64_t _AtomicUint64::getAndSub(uint64_t val) {
    //return __sync_fetch_and_sub(&value,val);
    //long v = mValue;
    //mValue -= val;
    return mValue.fetch_sub(val);
}

uint64_t _AtomicUint64::getAndAnd(uint64_t val) {
    //return __sync_fetch_and_and(&value,val);
    //long v = mValue;
    //mValue &= val;
    return mValue.fetch_and(val);
}

uint64_t _AtomicUint64::getAndOr(uint64_t val) {
    //return __sync_fetch_and_or(&value,val);
    //long v = mValue;
    //mValue |= val;
    return mValue.fetch_or(val);
}

uint64_t _AtomicUint64::getAndxor(uint64_t val) {
    //return __sync_fetch_and_xor(&value,val);
    //long v = mValue;
    //mValue |= ~val;
    return mValue.fetch_or(~val);
}

void _AtomicUint64::set(uint64_t val) {
    //__sync_bool_compare_and_swap(&value,value,val);
    mValue = val;
}

uint64_t _AtomicUint64::get() {
    return mValue;
}

}