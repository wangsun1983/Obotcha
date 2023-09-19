#ifndef __OBOTCHA_HTTP_HPACK_HUFFMAN_ENCODER_HPP__
#define __OBOTCHA_HTTP_HPACK_HUFFMAN_ENCODER_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ByteArrayWriter.hpp"

namespace obotcha {

DECLARE_CLASS(HPackHuffmanEncoder) {

public:
    uint32_t getEncodedLength(String) const;

    ByteArray encode(String) const;
    void encode(ByteArrayWriter,String) const;
};

}

#endif
