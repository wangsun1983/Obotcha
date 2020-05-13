#ifndef __OBOTCHA_HTTP_V2_HUFFMAN_ENCODER_HPP__
#define __OBOTCHA_HTTP_V2_HUFFMAN_ENCODER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Byte.hpp"
#include "List.hpp"
#include "ByteArray.hpp"

namespace obotcha {


DECLARE_SIMPLE_CLASS(HuffmanEncoder) {

public:
    _HuffmanEncoder(List<int> codes, List<byte> lengths);
    ByteArray encode(ByteArray data);
    ByteArray encode(ByteArray data, int off, int len);
    int getEncodedLength(ByteArray data);

private:
    List<int> codes;
    List<byte> lengths;

    
};



}

#endif
