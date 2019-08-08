#include "Crc32.hpp"
#include "FileInputStream.hpp"

namespace obotcha {
    
long _Crc32::encode(ByteArray b) {
    std::uint32_t result;
    // Process a raw buffer.
    result = crc32(0L,(const Bytef *)b->toValue(), b->size());

    return result;
}

long _Crc32::encode(String b) {
    std::uint32_t result;
    // Process a raw buffer.
    result = crc32(0L,(const Bytef *)b->toChars(), b->size());
    return result;
}

long _Crc32::encode(File f) {
    FileInputStream stream = createFileInputStream(f);
    stream->open();
    ByteArray arr = stream->readAll();
    stream->close();
    return encode(arr);
}

}
