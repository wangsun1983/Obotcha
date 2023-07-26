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

    int ret = deflateInit2(&mCompressStream, Z_DEFAULT_COMPRESSION, Z_DEFLATED,
                           -1 * compress_bit,
                           4, // memory level 1-9
                           Z_DEFAULT_STRATEGY);

    if (ret != Z_OK) {
        Trigger(InitializeException, "Zip init failed")
    }

    ret = inflateInit2(&mDecompressStream, -1 * decompress_bit);

    if (ret != Z_OK) {
        Trigger(InitializeException, "Zip init failed")
    }
}

ByteArray _ZipMemoryStream::compress(ByteArray in, int flush_mode) {
    unsigned char zipBuff[kZipCompressBuffSize] = {0};
    ByteArray out = nullptr;

    mCompressStream.avail_in = in->size();
    mCompressStream.next_in = in->toValue();
    int zipsize = 0;
    do {
        // Output to local buffer
        mCompressStream.avail_out = kZipCompressBuffSize;
        mCompressStream.next_out = &zipBuff[0];

        int ret = deflate(&mCompressStream, flush_mode);
        if (ret == Z_NEED_DICT || ret == Z_DATA_ERROR || ret == Z_MEM_ERROR) {
            return nullptr;
        }

        int size = kZipCompressBuffSize - mCompressStream.avail_out;
        if(out == nullptr) {
            out = createByteArray(zipBuff,size);
        } else {
            out->append(zipBuff, size);
        }
        zipsize += size;
    } while (mCompressStream.avail_out == 0);

    out->quickShrink(zipsize);
    return out;
}

ByteArray _ZipMemoryStream::decompress(ByteArray in, int flush_mode) {
    unsigned char zipBuff[kZipDecompressBuffSize];
    memset(zipBuff, 0, kZipDecompressBuffSize);
    // ByteArray out = createByteArray(kZipDecompressBuffSize);
    ByteArray out = nullptr;

    mDecompressStream.avail_in = in->size();
    mDecompressStream.next_in = in->toValue();

    do {
        // Output to local buffer
        mDecompressStream.avail_out = kZipDecompressBuffSize;
        mDecompressStream.next_out = zipBuff;

        inflate(&mDecompressStream, Z_SYNC_FLUSH);
        int size = kZipCompressBuffSize - mDecompressStream.avail_out;
        // out->append(zipBuff,size);
        if (out == nullptr) {
            out = createByteArray(zipBuff, size);
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
