#ifndef __OBOTCHA_CRC32_HPP__
#define __OBOTCHA_CRC32_HPP__

#include "zlib.h"

#include "Object.hpp"
#include "ByteArray.hpp"
#include "String.hpp"
#include "File.hpp"
#include "MessageDigestInterface.hpp"

namespace obotcha {

DECLARE_CLASS(Crc32) IMPLEMENTS(MessageDigestInterface) {

public:
    String encodeContent(ByteArray);
};

}
#endif
