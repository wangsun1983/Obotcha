#include "Crc32.hpp"
#include "FileInputStream.hpp"


namespace obotcha {
    
long _Crc32::encode(ByteArray b) {
    std::uint32_t result;

    // Process a raw buffer.
    result = crc32c::Crc32c(b->toValue(), b->size());

    return result;
}

long _Crc32::encode(String b) {
    std::uint32_t result;
    // Process a raw buffer.
    result = crc32c::Crc32c(b->toChars(), b->size());

    return result;
}

long _Crc32::encode(File f) {
    FileInputStream stream = createFileInputStream(f);
    ByteArray arr = stream->readAll();
    return encode(arr);
}

}
