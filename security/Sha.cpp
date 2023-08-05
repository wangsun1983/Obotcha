/**
 * @file Sha.cpp
 * @brief A class that can be used to compute the Sha1/Sha224/Sha256/Sha384/Sha512 of a data stream.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */
extern "C" {
#include "openssl/sha.h"
#include "openssl/crypto.h"
}

#include "Sha.hpp"
#include "Log.hpp"

namespace obotcha {

_Sha::_Sha(int type):mType(type) {
}

String _Sha::encodeContent(ByteArray data) {
    return convert(encryptRawData(data));
}

ByteArray _Sha::encryptRawData(ByteArray data) {
    ByteArray encryptData = nullptr;

    switch(mType) {
        case SHA_1: {
            encryptData = createByteArray(SHA_DIGEST_LENGTH);
            calc_stringSHA1((char *)data->toValue(),data->size(),encryptData->toValue());
        } break;

        case SHA_224: {
            encryptData = createByteArray(SHA224_DIGEST_LENGTH);
            calc_stringSHA224((char *)data->toValue(),data->size(),encryptData->toValue());
        } break;

        case SHA_256: {
            encryptData = createByteArray(SHA256_DIGEST_LENGTH);
            calc_stringSHA256((char *)data->toValue(),data->size(),encryptData->toValue());
        } break;

        case SHA_384: {
            encryptData = createByteArray(SHA384_DIGEST_LENGTH);
            calc_stringSHA384((char *)data->toValue(),data->size(),encryptData->toValue());
        } break;

        case SHA_512: {
            encryptData = createByteArray(SHA512_DIGEST_LENGTH);
            calc_stringSHA512((char *)data->toValue(),data->size(),encryptData->toValue());
        } break;

        default:
            LOG(ERROR)<<"Sha encryptRawData,unknow type:"<<mType;
        break;
    }

    return encryptData;
}

String _Sha::encodeFile(File file) {
    ByteArray encryptData = nullptr;

    switch(mType) {
        case SHA_1: {
            encryptData = createByteArray(SHA_DIGEST_LENGTH);
            calc_fileSHA1(file->getAbsolutePath()->toChars(),encryptData->toValue());
        } break;

        case SHA_224: {
            encryptData = createByteArray(SHA224_DIGEST_LENGTH);
            calc_fileSHA224(file->getAbsolutePath()->toChars(),encryptData->toValue());
        } break;

        case SHA_256: {
            encryptData = createByteArray(SHA256_DIGEST_LENGTH);
            calc_fileSHA256(file->getAbsolutePath()->toChars(),encryptData->toValue());
        } break;

        case SHA_384: {
            encryptData = createByteArray(SHA384_DIGEST_LENGTH);
            calc_fileSHA384(file->getAbsolutePath()->toChars(),encryptData->toValue());
        } break;

        case SHA_512: {
            encryptData = createByteArray(SHA512_DIGEST_LENGTH);
            calc_fileSHA512(file->getAbsolutePath()->toChars(),encryptData->toValue());
        } break;

        default:
            LOG(ERROR)<<"Sha encodeFile,unknow type:"<<mType;
        break;
    }

    if(encryptData != nullptr) {
        return convert(encryptData)->toString();
    }

    return nullptr;
}

#define CALC_FILE_SHA(SHAX) \
    char buf[4096] = {0};\
    int len = 0;\
    if (NULL == filename || NULL == dgst) {\
        return;\
    }\
    FILE *fp = fopen(filename, "rb");\
    if (NULL == fp) {\
        return;\
    }\
    SHAX##_Init(&ctx);\
    while ((len = fread(buf, 1, 4096, fp)) > 0) {\
        SHAX##_Update(&ctx, buf, len);\
        memset(buf, 0, len);\
    }\
    SHAX##_Final(dgst, &ctx);\
    fclose(fp);\


void _Sha::calc_fileSHA1(const char *filename,unsigned char *dgst) const {
    SHA_CTX ctx;
    CALC_FILE_SHA(SHA1)
}

void _Sha::calc_fileSHA224(const char *filename,unsigned char *dgst) const {
    SHA256_CTX ctx;
    CALC_FILE_SHA(SHA224)
}

void _Sha::calc_fileSHA256(const char *filename,unsigned char *dgst) const {
    SHA256_CTX ctx;
    CALC_FILE_SHA(SHA256)
}

void _Sha::calc_fileSHA384(const char *filename,unsigned char *dgst) const {
    SHA512_CTX ctx;
    CALC_FILE_SHA(SHA384)
}

void _Sha::calc_fileSHA512(const char *filename,unsigned char *dgst) const {
    SHA512_CTX ctx;
    CALC_FILE_SHA(SHA512)
}

#define CALC_STRING_SHA(SHAX) \
    if (NULL == content || NULL == dgst) { \
        return;\
    }\
    SHAX##_Init(&ctx); \
    SHAX##_Update(&ctx, content, length);\
    SHAX##_Final(dgst, &ctx);\

void _Sha::calc_stringSHA1(const char *content,int length,unsigned char *dgst) const {
    SHA_CTX ctx;
    CALC_STRING_SHA(SHA1)
}

void _Sha::calc_stringSHA224(const char *content,int length,unsigned char *dgst) const {
    SHA256_CTX ctx;
    CALC_STRING_SHA(SHA224)
}

void _Sha::calc_stringSHA256(const char *content,int length,unsigned char *dgst) const {
    SHA256_CTX ctx;
    CALC_STRING_SHA(SHA256)
}

void _Sha::calc_stringSHA384(const char *content,int length,unsigned char *dgst) const {
    SHA512_CTX ctx;
    CALC_STRING_SHA(SHA384)
}

void _Sha::calc_stringSHA512(const char *content,int length,unsigned char *dgst) const {
    SHA512_CTX ctx;
    CALC_STRING_SHA(SHA512)
}

ByteArray _Sha::convert(ByteArray data) const {
    int length = data->size();
    const byte *content = data->toValue();

    ByteArray result = createByteArray(length*2+1);
    char *mdString = (char *)result->toValue();

    for (int i = 0; i < length; i++) {
        sprintf(&mdString[i*2], "%02x", (unsigned int)content[i]);    
    }
    return result;
}

}
