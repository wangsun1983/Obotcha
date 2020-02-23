#include "Object.hpp"
#include "StrongPointer.hpp"
#include "HttpV2HuffmanEncoder.hpp"
#include "IllegalStateException.hpp"
#include "IllegalArgumentException.hpp"
#include "NullPointerException.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"
#include "ByteArrayWriter.hpp"
#include "Math.hpp"
#include "HttpV2HpackUtil.hpp"

namespace obotcha {

_HuffmanEncoder::_HuffmanEncoder(List<int> codes, List<byte> lengths) {
    this->codes = codes;
    this->lengths = lengths;
}

ByteArray _HuffmanEncoder::encode(ByteArray data) {
    return encode(data, 0, data->size());
}

ByteArray _HuffmanEncoder::encode(ByteArray data, int off, int len) {
    ByteArrayWriter writer = createByteArrayWriter();

    if (data == nullptr) {
      throw NullPointerException("data");
    } else if (off < 0 || len < 0 || (off + len) < 0 || off > data->size() || (off + len) > data->size()) {
      throw ArrayIndexOutOfBoundsException("data");
    } else if (len == 0) {
      return nullptr;
    }

    long current = 0;
    int n = 0;

    for (int i = 0; i < len; i++) {
      int b = data->at(off + i) & 0xFF;
      int code = codes[b];
      int nbits = lengths[b];

      current <<= nbits;
      current |= code;
      n += nbits;

      while (n >= 8) {
        n -= 8;
        writer->writeInt(((int)(current >> n)));
      }
    }

    if (n > 0) {
      current <<= (8 - n);
      current |= ((unsigned)0xFF >> n); // this should be EOS symbol
      writer->writeInt((int)current);
    }

    return writer->getByteArray();
}

int _HuffmanEncoder::getEncodedLength(ByteArray data) {
    if (data == nullptr) {
      throw NullPointerException("data");
    }
    long len = 0;

    for(int i = 0;i<data->size();i++) {
        len += lengths[data->at(i) & 0xFF];
    }

    return (int)((len + 7) >> 3);
}

}
