#include "HPackHuffmanEncoder.hpp"
#include "HPack.hpp"
#include "ByteArrayWriter.hpp"

namespace obotcha {

uint32_t _HPackHuffmanEncoder::getEncodedLength(String data) {
    uint32_t len = 0;
    int size = data->size();
    const char *p = data->toChars();

    for (int i = 0; i < size; i++) {
        len += st(HPack)::HuffmanCodesLength[p[i] & 0xFF];
    }
    return (uint32_t) ((len + 7) >> 3);
}

void _HPackHuffmanEncoder::encode(ByteArrayWriter writer,String data) {
    long current = 0;
    int n = 0;
    const char *p = data->toChars();
    int size = data->size();
    
    for (int i = 0; i < size; i++) {
        int b = p[i] & 0xFF;
        int code = st(HPack)::HuffmanCodes[b];
        int nbits = st(HPack)::HuffmanCodesLength[b];

        current <<= nbits;
        current |= code;
        n += nbits;
        printf("n is %d,code is %x,nbits is %d \n",n,code,nbits);
        while (n >= 8) {
            n -= 8;
            printf("write data is %x \n",current>>n);
            writer->writeByte((current >> n));
        }
    }

    if (n > 0) {
        current <<= (8 - n);
        current |= ((unsigned int)0xFF >> n); // this should be EOS symbol
        printf("write2 data is %x \n",current);
        writer->writeByte((int) current);
    }
}

ByteArray _HPackHuffmanEncoder::encode(String data) {
    int size = data->size();
    //get codec length
    int length = getEncodedLength(data);
    printf("length is %d,size is %d\n",length,size);
    ByteArray out = createByteArray(length);
    ByteArrayWriter writer = createByteArrayWriter(out);
    encode(writer,data);
    
    return out;
}

}
