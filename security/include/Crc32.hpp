#ifndef __CRC32_HPP__
#define __CRC32_HPP__

#include "crc32c/crc32c.h"

#include "ByteArray.hpp"
#include "String.hpp"
#include "File.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Crc32) {

public:
    long encode(ByteArray);
    long encode(String);
    long encode(File);
};

}
#endif
