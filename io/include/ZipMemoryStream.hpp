#ifndef __OBOTCHA_ZIP_MEMORY_STREAM_HPP__
#define __OBOTCHA_ZIP_MEMORY_STREAM_HPP__

#include <fstream>
#include <iostream>

#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

extern "C" {
#include "zlib.h"
#include "zip.h"
#include "unzip.h"
}

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "File.hpp"
#include "InputStream.hpp"
#include "ByteArray.hpp"
#include "ZipFile.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(ZipMemoryStream) {
public:
    _ZipMemoryStream(int compress_bit = 15,int decompress_bit = 15);

    ByteArray compress(ByteArray,int flush = Z_FULL_FLUSH);
    ByteArray decompress(ByteArray,int flush = Z_FULL_FLUSH);

private:
    z_stream mCompressStream;
    z_stream mDecompressStream;    
};

}
#endif
