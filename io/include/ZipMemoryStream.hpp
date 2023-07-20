#ifndef __OBOTCHA_ZIP_MEMORY_STREAM_HPP__
#define __OBOTCHA_ZIP_MEMORY_STREAM_HPP__

extern "C" {
    #include "unzip.h"
    #include "zip.h"
    #include "zlib.h"
}

#include "Object.hpp"
#include "ByteArray.hpp"

namespace obotcha {

DECLARE_CLASS(ZipMemoryStream) {
  public:
    _ZipMemoryStream(int compress_bit = 15, int decompress_bit = 15);
    ~_ZipMemoryStream();
    ByteArray compress(ByteArray, int flush = Z_FULL_FLUSH);
    ByteArray decompress(ByteArray, int flush = Z_FULL_FLUSH);

  private:
    z_stream mCompressStream;
    z_stream mDecompressStream;
    static const int kZipCompressBuffSize;
    static const int kZipDecompressBuffSize;
};

} // namespace obotcha
#endif
