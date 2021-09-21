#ifndef __OBOTCHA_ZIP_MEMORY_STREAM_HPP__
#define __OBOTCHA_ZIP_MEMORY_STREAM_HPP__

#include <fstream>
#include <iostream>

#include <dirent.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>

extern "C" {
#include "unzip.h"
#include "zip.h"
#include "zlib.h"
}

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ByteArray.hpp"
#include "File.hpp"
#include "InputStream.hpp"
#include "String.hpp"
#include "ZipFile.hpp"

namespace obotcha {

DECLARE_CLASS(ZipMemoryStream) {
  public:
    _ZipMemoryStream(int compress_bit = 15, int decompress_bit = 15);

    ByteArray compress(ByteArray, int flush = Z_FULL_FLUSH);
    ByteArray decompress(ByteArray, int flush = Z_FULL_FLUSH);

  private:
    z_stream mCompressStream;
    z_stream mDecompressStream;
};

} // namespace obotcha
#endif
