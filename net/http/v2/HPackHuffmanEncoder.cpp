#include "HPackHuffmanEncoder.hpp"
#include "HPack.hpp"
#include "ByteArrayWriter.hpp"

namespace obotcha {

uint32_t _HPackHuffmanEncoder::getEncodedLength(String data) const {
    uint32_t len = 0;
    auto size = data->size();
    const char *p = data->toChars();

    for (size_t i = 0; i < size; i++) {
        len += st(HPack)::HuffmanCodesLength[p[i] & 0xFF];
    }
    return (len + 7) >> 3;
}

void _HPackHuffmanEncoder::encode(ByteArrayWriter writer,String data) const {
    long current = 0;
    int n = 0;
    const char *p = data->toChars();
    auto size = data->size();

    for (size_t i = 0; i < size; i++) {
        int b = p[i] & 0xFF;
        int code = st(HPack)::HuffmanCodes[b];
        int nbits = st(HPack)::HuffmanCodesLength[b];

        current <<= nbits;
        current |= code;
        n += nbits;
        while (n >= 8) {
            n -= 8;
            writer->write<byte>((current >> n));
        }
    }

    if (n > 0) {
        current <<= (8 - n);
        current |= ((unsigned int)0xFF >> n); // this should be EOS symbol
        writer->write<byte>((int) current);
    }
}

ByteArray _HPackHuffmanEncoder::encode(String data) const {
    //get codec length
    int length = getEncodedLength(data);
    ByteArray out = ByteArray::New(length);
    ByteArrayWriter writer = ByteArrayWriter::New(out);
    encode(writer,data);

    return out;
}

}
