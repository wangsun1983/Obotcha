#ifndef __OBOTCHA_HTTP_HPACK_HUFFMAN_ENCODER_HPP__
#define __OBOTCHA_HTTP_HPACK_HUFFMAN_ENCODER_HPP__

#include <map>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Byte.hpp"

namespace obotcha {

DECLARE_CLASS(HPackHuffmanEncoder) {

public:
    uint32_t getEncodedLength(String);
    ByteArray encode(String);
};

}

#endif
