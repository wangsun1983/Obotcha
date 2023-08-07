#include "AtomicInteger.hpp"

namespace obotcha {

_AtomicInteger::_AtomicInteger(int val):mValue(val) { 
}

int _AtomicInteger::incrementAndGet() {
    return __sync_add_and_fetch(&mValue, 1);
}

int _AtomicInteger::decrementAndGet() {
    return __sync_add_and_fetch(&mValue, -1);
}

int _AtomicInteger::addAndGet(int val) {
    return __sync_add_and_fetch(&mValue, val);
}

int _AtomicInteger::subAndGet(int val) {
    return __sync_sub_and_fetch(&mValue, val);
}

int _AtomicInteger::andAndGet(int val) {
    return __sync_and_and_fetch(&mValue, val);
}

int _AtomicInteger::orAndGet(int val) {
    return __sync_or_and_fetch(&mValue, val);
}

int _AtomicInteger::xorAndGet(int val) {
    return __sync_xor_and_fetch(&mValue, val);
}

int _AtomicInteger::getAndIncrement() {
    return __sync_fetch_and_add(&mValue, 1);
}

int _AtomicInteger::getAndDecrement() {
    return __sync_fetch_and_add(&mValue, -1);
}

int _AtomicInteger::getAndAdd(int val) {
    return __sync_fetch_and_add(&mValue, val);
}

int _AtomicInteger::getAndSub(int val) {
    return __sync_fetch_and_sub(&mValue, val);
}

int _AtomicInteger::getAndAnd(int val) {
    return __sync_fetch_and_and(&mValue, val);
}

int _AtomicInteger::getAndOr(int val) {
    return __sync_fetch_and_or(&mValue, val);
}

int _AtomicInteger::getAndxor(int val) {
    return __sync_fetch_and_xor(&mValue, val);
}

void _AtomicInteger::set(int val) {
    __sync_bool_compare_and_swap(&mValue, mValue, val);
}

int _AtomicInteger::compareAndSet(int val) {
    int result = mValue;
    __sync_bool_compare_and_swap(&mValue, mValue, val);
    return result;
}

int _AtomicInteger::get() { 
    return getAndAdd(0); 
}

} // namespace obotcha