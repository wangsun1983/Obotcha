#ifndef __OBOTCHA_CRC32_HPP__
#define __OBOTCHA_CRC32_HPP__

#include "zlib.h"

#include "ByteArray.hpp"
#include "String.hpp"
#include "File.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Crc32) {

public:
    uint32_t encode(ByteArray);
    uint32_t encode(String);
    uint32_t encode(File);
};

}
#endif
