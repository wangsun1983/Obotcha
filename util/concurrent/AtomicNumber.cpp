#include "AtomicNumber.hpp"

namespace obotcha {

AtomicByte createAtomicByte(byte value) {
    return createAtomicNumber<byte>(value);
}

AtomicInteger createAtomicInteger(int value) {
    return createAtomicNumber<int>(value);
}

AtomicLong createAtomicLong(long value) {
    return createAtomicNumber<long>(value);
}

AtomicUint8 createAtomicUint8(uint8_t value) {
    return createAtomicNumber<uint8_t>(value);
}

AtomicUint16 createAtomicUint16(uint16_t value) {
    return createAtomicNumber<uint16_t>(value);
}

AtomicUint32 createAtomicUint32(uint32_t value) {
    return createAtomicNumber<uint32_t>(value);
}

AtomicUint64 createAtomicUint64(uint64_t value) {
    return createAtomicNumber<uint64_t>(value);
}

} // namespace obotcha
