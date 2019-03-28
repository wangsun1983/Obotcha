#include "Crc32.hpp"


namespace obotcha {
    
long _Crc32::verify(ByteArray b) {
    std::uint32_t result;

    // Process a raw buffer.
    result = crc32c::Crc32c(b->toValue(), b->size());

    return result;
}

long _Crc32::verify(String b) {
    std::uint32_t result;
    // Process a raw buffer.
    result = crc32c::Crc32c(b->toChars(), b->size());

    return result;
}

}
