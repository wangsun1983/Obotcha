#ifndef __OBOTCHA_ATOMIC_NUMBER_HPP__
#define __OBOTCHA_ATOMIC_NUMBER_HPP__

#include <atomic>

#include "Object.hpp"
#include "Byte.hpp"

namespace obotcha {

DECLARE_TEMPLATE_CLASS(AtomicNumber,T) {
public:
    explicit _AtomicNumber(T val):mValue(val) {
    }

    T incrementAndGet() { 
        return ++mValue; 
    }

    T decrementAndGet() { 
        return --mValue; 
    }

    T addAndGet(T val) {
        mValue += val;
        return mValue;
    }

    T subAndGet(T val) {
        mValue -= val;
        return mValue;
    }

    T andAndGet(T val) {
        mValue &= val;
        return mValue;
    }

    T orAndGet(T val) {
        mValue |= val;
        return mValue;
    }

    T xorAndGet(T val) {
        mValue |= ~val;
        return mValue;
    }

    T getAndIncrement() { 
        return mValue++; 
    }

    T getAndDecrement() { 
        return mValue--; 
    }

    T getAndAdd(T val) {
        return mValue.fetch_add(val);
    }

    T getAndSub(T val) {
        return mValue.fetch_sub(val);
    }

    T getAndAnd(T val) {
        return mValue.fetch_and(val);
    }

    T getAndOr(T val) { 
        return mValue.fetch_or(val); 
    }

    T getAndxor(T val) {
        return mValue.fetch_or(~val);
    }

    void set(T val) { 
        mValue = val; 
    }

    T get() const { 
        return mValue; 
    }

  private:
    std::atomic<T> mValue;
};

using AtomicByte = sp<_AtomicNumber<byte>>;
using AtomicInteger = sp<_AtomicNumber<int>>;
using AtomicLong = sp<_AtomicNumber<long>>;
using AtomicUint8 = sp<_AtomicNumber<uint8_t>>;
using AtomicUint16 = sp<_AtomicNumber<uint16_t>>;
using AtomicUint32 =sp<_AtomicNumber<uint32_t>>;
using AtomicUint64 = sp<_AtomicNumber<uint64_t>>;

AtomicByte createAtomicByte(byte);
AtomicInteger createAtomicInteger(int);
AtomicLong createAtomicLong(long);
AtomicUint8 createAtomicUint8(uint8_t);
AtomicUint16 createAtomicUint16(uint16_t);
AtomicUint32 createAtomicUint32(uint32_t);
AtomicUint64 createAtomicUint64(uint64_t);

} // namespace obotcha
#endif
