/**
 * @file Crc32.cpp
 * @brief A class that can be used to compute the CRC-32 of a data stream.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */

#include "Crc32.hpp"
#include "FileInputStream.hpp"
#include "Inspect.hpp"

namespace obotcha {
    
uint32_t _Crc32::encode(ByteArray b) {
    Inspect(b == nullptr,0)
    return crc32(0L,(const Bytef *)b->toValue(), b->size());
}

uint32_t _Crc32::encode(String b) {
    Inspect(b == nullptr,0)
    return crc32(0L,(const Bytef *)b->toChars(), b->size());
}

uint32_t _Crc32::encode(File f) {
    Inspect(f == nullptr || !f->exists(),0)

    FileInputStream stream = createFileInputStream(f);
    stream->open();
    ByteArray arr = stream->readAll();
    stream->close();
    return encode(arr);
}

}
