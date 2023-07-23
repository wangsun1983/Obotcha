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
    
String _Crc32::encodeContent(ByteArray b) {
    Inspect(b == nullptr,0)
    return createString(crc32(0L,(const Bytef *)b->toValue(), b->size()));
}

}
