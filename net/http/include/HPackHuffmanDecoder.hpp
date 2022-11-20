#ifndef __OBOTCHA_HTTP_HPACK_HUFFMAN_DECODER_HPP__
#define __OBOTCHA_HTTP_HPACK_HUFFMAN_DECODER_HPP__

#include "Object.hpp"
#include "ByteArray.hpp"
#include "String.hpp"
#include "Byte.hpp"

namespace obotcha {

DECLARE_CLASS(HPackHuffmanDecoder) {

public:
    ByteArray decode(ByteArray);
    
private:
    static const byte HUFFMAN_COMPLETE;
    static const byte HUFFMAN_EMIT_SYMBOL;
    static const byte HUFFMAN_FAIL;

    static const int HUFFMAN_COMPLETE_SHIFT;
    static const int HUFFMAN_EMIT_SYMBOL_SHIFT;
    static const int HUFFMAN_FAIL_SHIFT;

    static const int HUFFS[];

    bool processNibble(int input,int &state,int &k,byte *dest);
};

}

#endif
