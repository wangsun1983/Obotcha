#include "Crc32.hpp"
#include "FileInputStream.hpp"
#include "NullPointerException.hpp"
#include "FileNotFoundException.hpp"

namespace obotcha {
    
long _Crc32::encode(ByteArray b) {
    if(b == nullptr) {
        throw createNullPointerException("Crc32 encode param is nullptr");
    }

    std::uint32_t result;
    // Process a raw buffer.
    result = crc32(0L,(const Bytef *)b->toValue(), b->size());

    return result;
}

long _Crc32::encode(String b) {
    if(b == nullptr) {
        throw createNullPointerException("Crc32 encode param is nullptr");
    }

    std::uint32_t result;
    // Process a raw buffer.
    result = crc32(0L,(const Bytef *)b->toChars(), b->size());
    return result;
}

long _Crc32::encode(File f) {
    if(f == nullptr) {
        throw createNullPointerException("Crc32 encode param is nullptr");
    }

    if(!f->exists()) {
        throw createFileNotFoundException("Crc32 encode file not exists");
    }

    FileInputStream stream = createFileInputStream(f);
    stream->open();
    ByteArray arr = stream->readAll();
    stream->close();
    return encode(arr);
}

}
