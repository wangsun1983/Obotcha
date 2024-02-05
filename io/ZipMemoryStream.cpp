/**
 * @file ZipMemoryStream.cpp
 * @brief ZipMemoryStream is meant for compressing/decompressing a memory data
 *        with Zip compression algorithm 
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2024-01-03
 * @license none
 */

#include "ZipMemoryStream.hpp"
#include "ByteArray.hpp"
#include "InitializeException.hpp"

namespace obotcha {

const int st(ZipMemoryStream)::kZipCompressBuffSize = 1024*4;
const int st(ZipMemoryStream)::kZipDecompressBuffSize = 1024*4;

_ZipMemoryStream::_ZipMemoryStream(int compress_bit, int decompress_bit) {
    mCompressStream.zalloc = Z_NULL;
    mCompressStream.zfree = Z_NULL;
    mCompressStream.opaque = Z_NULL;

    mDecompressStream.zalloc = Z_NULL;
    mDecompressStream.zfree = Z_NULL;
    mDecompressStream.opaque = Z_NULL;
    mDecompressStream.avail_in = 0;
    mDecompressStream.next_in = Z_NULL;

    if (deflateInit2(&mCompressStream, Z_DEFAULT_COMPRESSION, Z_DEFLATED,
                           -1 * compress_bit,
                           4, // memory level 1-9
                           Z_DEFAULT_STRATEGY) != Z_OK) {
        Trigger(InitializeException, "Zip init failed")
    }

    if (inflateInit2(&mDecompressStream, -1 * decompress_bit) != Z_OK) {
        Trigger(InitializeException, "Zip init failed")
    }
}

ByteArray _ZipMemoryStream::compress(ByteArray in, int flush_mode) {
    ByteArray zipBuff = createByteArray(kZipCompressBuffSize);
    ByteArray out = nullptr;

    mCompressStream.avail_in = in->size();
    mCompressStream.next_in = in->toValue();
    do {
        // Output to local buffer
        mCompressStream.avail_out = kZipCompressBuffSize;
        mCompressStream.next_out = zipBuff->toValue();
        if (int ret = deflate(&mCompressStream, flush_mode);
            ret == Z_NEED_DICT || ret == Z_DATA_ERROR || ret == Z_MEM_ERROR) {
            return nullptr;
        }

        int size = kZipCompressBuffSize - mCompressStream.avail_out;
        if(out == nullptr) {
            out = createByteArray(zipBuff,0,size);
        } else {
            out->append(zipBuff, size);
        }
    } while (mCompressStream.avail_out == 0);

    return out;
}

ByteArray _ZipMemoryStream::decompress(ByteArray in, [[maybe_unused]]int flush_mode) {
    ByteArray zipBuff = createByteArray(kZipDecompressBuffSize);
    ByteArray out = nullptr;

    mDecompressStream.avail_in = in->size();
    mDecompressStream.next_in = in->toValue();
    do {
        // Output to local buffer
        mDecompressStream.avail_out = kZipDecompressBuffSize;
        mDecompressStream.next_out = zipBuff->toValue();

        inflate(&mDecompressStream, Z_SYNC_FLUSH);
        int size = kZipCompressBuffSize - mDecompressStream.avail_out;
        if (out == nullptr) {
            out = createByteArray(zipBuff, 0,size);
        } else {
            out->append(zipBuff, size);
        }
    } while (mDecompressStream.avail_out == 0);

    return out;
}

_ZipMemoryStream::~_ZipMemoryStream() {
    deflateEnd(&mCompressStream);
    inflateEnd(&mDecompressStream);
}


} // namespace obotcha
