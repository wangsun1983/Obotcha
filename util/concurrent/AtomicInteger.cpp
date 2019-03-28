#include "AtomicInteger.hpp"

namespace obotcha {

_AtomicInteger::_AtomicInteger(int val) {
    value = val;
}

int _AtomicInteger::incrementAndGet() {
    return __sync_add_and_fetch(&value,1);
}

int _AtomicInteger::decrementAndGet() {
    return __sync_add_and_fetch(&value,-1);
}

int _AtomicInteger::addAndGet(int val) {
    return __sync_add_and_fetch(&value,val);
}

int _AtomicInteger::subAndGet(int val) {
    return __sync_sub_and_fetch(&value,val);
}

int _AtomicInteger::andAndGet(int val) {
    return __sync_and_and_fetch(&value,val);
}

int _AtomicInteger::orAndGet(int val) {
    return __sync_or_and_fetch(&value,val);
}

int _AtomicInteger::xorAndGet(int val) {
    return __sync_xor_and_fetch(&value,val);
}

int _AtomicInteger::getAndIncrement() {
    return __sync_fetch_and_add(&value,1);
}

int _AtomicInteger::getAndDecrement() {
    return __sync_fetch_and_add(&value,-1);
}

int _AtomicInteger::getAndAdd(int val) {
    return __sync_fetch_and_add(&value,val);
}

int _AtomicInteger::getAndSub(int val) {
    return __sync_fetch_and_sub(&value,val);
}

int _AtomicInteger::getAndAnd(int val) {
    return __sync_fetch_and_and(&value,val);
}

int _AtomicInteger::getAndOr(int val) {
    return __sync_fetch_and_or(&value,val);
}

int _AtomicInteger::getAndxor(int val) {
    return __sync_fetch_and_xor(&value,val);
    
}

void _AtomicInteger::set(int val) {
    __sync_bool_compare_and_swap(&value,value,val);
}

int _AtomicInteger::get() {
    return value;
}

}