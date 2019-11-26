#include "ZipMemoryStream.hpp"
#include "InitializeException.hpp"
#include "ByteArray.hpp"

namespace obotcha {

#define ZIP_COMPRESS_BUFF_SIZE 1024*4
#define ZIP_DECOMPRESS_BUFF_SIZE 1024*4

_ZipMemoryStream::_ZipMemoryStream(int compress_bit,int decompress_bit) {
    mCompressStream.zalloc = Z_NULL;
    mCompressStream.zfree = Z_NULL;
    mCompressStream.opaque = Z_NULL;

    mDecompressStream.zalloc = Z_NULL;
    mDecompressStream.zfree = Z_NULL;
    mDecompressStream.opaque = Z_NULL;
    mDecompressStream.avail_in = 0;
    mDecompressStream.next_in = Z_NULL;

    int ret = deflateInit2(
            &mCompressStream,
            Z_DEFAULT_COMPRESSION,
            Z_DEFLATED,
            -1*compress_bit,
            4, // memory level 1-9
            Z_DEFAULT_STRATEGY
    );

    if(ret != Z_OK){
        throw createInitializeException("Zip init failed");
    }

    ret = inflateInit2(
        &mDecompressStream,
        -1*decompress_bit
    );

    if (ret != Z_OK) {
        throw createInitializeException("Zip init failed");
    }
}

ByteArray _ZipMemoryStream::compress(ByteArray in, int flush_mode) {
    int ret;
    unsigned char zipBuff[ZIP_COMPRESS_BUFF_SIZE];
    memset(zipBuff,0,ZIP_COMPRESS_BUFF_SIZE);
    ByteArray out = createByteArray(ZIP_COMPRESS_BUFF_SIZE);
    
    mCompressStream.avail_in = in->size();
    mCompressStream.next_in = in->toValue();
    printf("in->size() is %d \n",in->size());
    int zipsize = 0;
    do {
        // Output to local buffer
        mCompressStream.avail_out = ZIP_COMPRESS_BUFF_SIZE;
        mCompressStream.next_out = &zipBuff[0];

        ret = deflate(&mCompressStream, flush_mode);
        if (ret == Z_NEED_DICT || ret == Z_DATA_ERROR || ret == Z_MEM_ERROR) {
            return nullptr;
        }

        int size = ZIP_COMPRESS_BUFF_SIZE - mCompressStream.avail_out;
        printf("size is %d,zip is %s,avail_out is %d,mCompressStream.avail_out is %d \n",size,zipBuff,mCompressStream.avail_out);
        out->append(zipBuff,size);
        zipsize += size;
    } while (mCompressStream.avail_out == 0);

    out->qucikShrink(zipsize);
    return out;
}

ByteArray _ZipMemoryStream::decompress(ByteArray in,int flush_mode) {
    unsigned char zipBuff[ZIP_DECOMPRESS_BUFF_SIZE];
    memset(zipBuff,0,ZIP_DECOMPRESS_BUFF_SIZE);
    ByteArray out = createByteArray(ZIP_DECOMPRESS_BUFF_SIZE);
    
    mDecompressStream.avail_in = in->size();
    printf("decompress size is %d,zip is %s \n",in->size(),in->toString());
    mDecompressStream.next_in = in->toValue();
    do {
        // Output to local buffer
        mDecompressStream.avail_out = ZIP_DECOMPRESS_BUFF_SIZE;
        mDecompressStream.next_out = zipBuff;

        inflate(&mDecompressStream, flush_mode);
        printf("decompress trace1 zip is %s \n",zipBuff);

        int size = ZIP_COMPRESS_BUFF_SIZE - mDecompressStream.avail_out;
        printf("decompress is %d,zip is %s,avail_out is %d,mCompressStream.avail_out is %d \n",size,zipBuff,mDecompressStream.avail_out);
        
        out->append(zipBuff,size);
    } while (mDecompressStream.avail_out == 0);

    return out;
}

}
