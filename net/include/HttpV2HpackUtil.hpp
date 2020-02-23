#ifndef __HTTP_V2_HPACK_UTIL__
#define __HTTP_V2_HPACK_UTIL__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Byte.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpV2HpackUtil) {

public:
    static const int HuffmanCode[];
    static const byte HuffmanLength[];
    static const int HUFFMAN_EOS;
};

}

#endif