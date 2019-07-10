#include "AtomicLong.hpp"

namespace obotcha {

_AtomicLong::_AtomicLong(long val) {
    mValue = val;
}

long _AtomicLong::incrementAndGet() {
    //return __sync_add_and_fetch(&value,1);
    return ++mValue;
}

long _AtomicLong::decrementAndGet() {
    //return __sync_add_and_fetch(&value,-1);
    return --mValue;
}

long _AtomicLong::addAndGet(long val) {
    //return __sync_add_and_fetch(&value,val);
    mValue+= val;
    return mValue;
}

long _AtomicLong::subAndGet(long val) {
    //return __sync_sub_and_fetch(&value,val);
    mValue -= val;
    return mValue;
}

long _AtomicLong::andAndGet(long val) {
    //return __sync_and_and_fetch(&value,val);
    mValue &= val;
    return mValue;
}

long _AtomicLong::orAndGet(long val) {
    //return __sync_or_and_fetch(&value,val);
    mValue |= val;
    return mValue;
}

long _AtomicLong::xorAndGet(long val) {
    //return __sync_xor_and_fetch(&value,val);
    mValue |= ~val;
    return mValue;
}

long _AtomicLong::getAndIncrement() {
    //return __sync_fetch_and_add(&value,1);
    return mValue++;
}

long _AtomicLong::getAndDecrement() {
    //return __sync_fetch_and_add(&value,-1);
    return mValue--;
}

long _AtomicLong::getAndAdd(long val) {
    //return __sync_fetch_and_add(&value,val);
    //long v = mValue;
    //mValue += val;
    return mValue.fetch_add(val);
}

long _AtomicLong::getAndSub(long val) {
    //return __sync_fetch_and_sub(&value,val);
    //long v = mValue;
    //mValue -= val;
    return mValue.fetch_sub(val);
}

long _AtomicLong::getAndAnd(long val) {
    //return __sync_fetch_and_and(&value,val);
    //long v = mValue;
    //mValue &= val;
    return mValue.fetch_and(val);
}

long _AtomicLong::getAndOr(long val) {
    //return __sync_fetch_and_or(&value,val);
    //long v = mValue;
    //mValue |= val;
    return mValue.fetch_or(val);
}

long _AtomicLong::getAndxor(long val) {
    //return __sync_fetch_and_xor(&value,val);
    //long v = mValue;
    //mValue |= ~val;
    return mValue.fetch_or(~val);
}

void _AtomicLong::set(long val) {
    //__sync_bool_compare_and_swap(&value,value,val);
    mValue = val;
}

long _AtomicLong::get() {
    return mValue;
}

}