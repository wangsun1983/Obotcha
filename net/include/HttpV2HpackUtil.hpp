#ifndef __OBOTCHA_HTTP_V2_HPACK_UTIL__
#define __OBOTCHA_HTTP_V2_HPACK_UTIL__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Byte.hpp"
#include "ByteArray.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpV2HpackUtil) {

public:
    static bool equals(ByteArray s1, ByteArray s2);
    static const int HuffmanCode[];
    static const byte HuffmanLength[];
    static const int HUFFMAN_EOS = 256;
};

}

#endif