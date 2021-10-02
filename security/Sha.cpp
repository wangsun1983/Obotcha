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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/crypto.h>

#include "FileInputStream.hpp"
#include "Sha.hpp"

namespace obotcha {

_Sha::_Sha(int type) {
    mType = type;
}

String _Sha::encrypt(String str) {
    unsigned char *data;
    int length;

    switch(mType) {
        case SHA_1: {
            unsigned char encryptData[SHA_DIGEST_LENGTH] = {0};
            calc_stringSHA1(str->toChars(),str->size(),encryptData);
            data = encryptData;
            length = SHA_DIGEST_LENGTH;
        }
        break;

        case SHA_224: {
            unsigned char encryptData[SHA224_DIGEST_LENGTH] = {0};
            calc_stringSHA224(str->toChars(),str->size(),encryptData);
            data = encryptData;
            length = SHA224_DIGEST_LENGTH;
        }
        break;

        case SHA_256: {
            unsigned char encryptData[SHA256_DIGEST_LENGTH] = {0};
            calc_stringSHA256(str->toChars(),str->size(),encryptData);
            data = encryptData;
            length = SHA256_DIGEST_LENGTH;
        }
        break;

        case SHA_384: {
            unsigned char encryptData[SHA384_DIGEST_LENGTH] = {0};
            calc_stringSHA384(str->toChars(),str->size(),encryptData);
            data = encryptData;
            length = SHA384_DIGEST_LENGTH;
        }
        break;

        case SHA_512: {
            unsigned char encryptData[SHA512_DIGEST_LENGTH] = {0};
            calc_stringSHA512(str->toChars(),str->size(),encryptData);
            data = encryptData;
            length = SHA512_DIGEST_LENGTH;
        }
        break;
    }

    return convert(data,length);
}

ByteArray _Sha::encryptRawData(ByteArray data) {
    unsigned char *encryptData = nullptr;
    int encryptLength = 0;

    switch(mType) {
        case SHA_1: {
            //unsigned char encryptData[SHA_DIGEST_LENGTH] = {0};
            encryptData = (unsigned char *)malloc(SHA_DIGEST_LENGTH);
            memset(encryptData,0,SHA_DIGEST_LENGTH);
            encryptLength = SHA_DIGEST_LENGTH;

            calc_stringSHA1((char *)data->toValue(),data->size(),encryptData);
        }
        break;

        case SHA_224: {
            //unsigned char encryptData[SHA224_DIGEST_LENGTH] = {0};
            encryptData = (unsigned char *)malloc(SHA224_DIGEST_LENGTH);
            memset(encryptData,0,SHA224_DIGEST_LENGTH);
            encryptLength = SHA224_DIGEST_LENGTH;

            calc_stringSHA224((char *)data->toValue(),data->size(),encryptData);
        }
        break;

        case SHA_256: {
            //unsigned char encryptData[SHA256_DIGEST_LENGTH] = {0};
            encryptData = (unsigned char *)malloc(SHA256_DIGEST_LENGTH);
            memset(encryptData,0,SHA256_DIGEST_LENGTH);
            encryptLength = SHA256_DIGEST_LENGTH;

            calc_stringSHA256((char *)data->toValue(),data->size(),encryptData);
        }
        break;

        case SHA_384: {
            //unsigned char encryptData[SHA384_DIGEST_LENGTH] = {0};
            encryptData = (unsigned char *)malloc(SHA384_DIGEST_LENGTH);
            memset(encryptData,0,SHA384_DIGEST_LENGTH);
            encryptLength = SHA384_DIGEST_LENGTH;

            calc_stringSHA384((char *)data->toValue(),data->size(),encryptData);
        }
        break;

        case SHA_512: {
            //unsigned char encryptData[SHA512_DIGEST_LENGTH] = {0};
            encryptData = (unsigned char *)malloc(SHA512_DIGEST_LENGTH);
            memset(encryptData,0,SHA512_DIGEST_LENGTH);
            encryptLength = SHA512_DIGEST_LENGTH;

            calc_stringSHA512((char *)data->toValue(),data->size(),encryptData);
        }
        break;
    }

    if(encryptData != nullptr) {
        auto result = createByteArray(encryptData,encryptLength);
        free(encryptData);
        return result;
    }

    return nullptr;
}

String _Sha::encrypt(File file) {
    unsigned char *encryptData = nullptr;
    int encryptLength = 0;

    switch(mType) {
        case SHA_1: {
            //unsigned char encryptData[SHA_DIGEST_LENGTH] = {0};
            encryptData = (unsigned char *)malloc(SHA_DIGEST_LENGTH);
            memset(encryptData,0,SHA_DIGEST_LENGTH);
            encryptLength = SHA_DIGEST_LENGTH;

            calc_fileSHA1(file->getAbsolutePath()->toChars(),encryptData);
        }
        break;

        case SHA_224: {
            //unsigned char encryptData[SHA224_DIGEST_LENGTH] = {0};
            encryptData = (unsigned char *)malloc(SHA224_DIGEST_LENGTH);
            memset(encryptData,0,SHA224_DIGEST_LENGTH);
            encryptLength = SHA224_DIGEST_LENGTH;

            calc_fileSHA224(file->getAbsolutePath()->toChars(),encryptData);
        }
        break;

        case SHA_256: {
            //unsigned char encryptData[SHA256_DIGEST_LENGTH] = {0};
            encryptData = (unsigned char *)malloc(SHA256_DIGEST_LENGTH);
            memset(encryptData,0,SHA256_DIGEST_LENGTH);
            encryptLength = SHA256_DIGEST_LENGTH;

            calc_fileSHA256(file->getAbsolutePath()->toChars(),encryptData);
        }
        break;

        case SHA_384: {
            //unsigned char encryptData[SHA384_DIGEST_LENGTH] = {0};
            encryptData = (unsigned char *)malloc(SHA384_DIGEST_LENGTH);
            memset(encryptData,0,SHA384_DIGEST_LENGTH);
            encryptLength = SHA384_DIGEST_LENGTH;

            calc_fileSHA384(file->getAbsolutePath()->toChars(),encryptData);
        }
        break;

        case SHA_512: {
            //unsigned char encryptData[SHA512_DIGEST_LENGTH] = {0};
            encryptData = (unsigned char *)malloc(SHA512_DIGEST_LENGTH);
            memset(encryptData,0,SHA512_DIGEST_LENGTH);
            encryptLength = SHA512_DIGEST_LENGTH;

            calc_fileSHA512(file->getAbsolutePath()->toChars(),encryptData);
        }
        break;
    }

    if(encryptData != nullptr) {
        String result = convert(encryptData,encryptLength);
        free(encryptData);
        return result;
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


void _Sha::calc_fileSHA1(const char *filename,unsigned char *dgst) {
    SHA_CTX ctx;
    CALC_FILE_SHA(SHA1)
}

void _Sha::calc_fileSHA224(const char *filename,unsigned char *dgst) {
    SHA256_CTX ctx;
    CALC_FILE_SHA(SHA224)
}

void _Sha::calc_fileSHA256(const char *filename,unsigned char *dgst) {
    SHA256_CTX ctx;
    CALC_FILE_SHA(SHA256)
}

void _Sha::calc_fileSHA384(const char *filename,unsigned char *dgst) {
    SHA512_CTX ctx;
    CALC_FILE_SHA(SHA384)
}

void _Sha::calc_fileSHA512(const char *filename,unsigned char *dgst) {
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

void _Sha::calc_stringSHA1(const char *content,int length,unsigned char *dgst) {
    SHA_CTX ctx;
    CALC_STRING_SHA(SHA1)
}

void _Sha::calc_stringSHA224(const char *content,int length,unsigned char *dgst) {
    SHA256_CTX ctx;
    CALC_STRING_SHA(SHA224)
}

void _Sha::calc_stringSHA256(const char *content,int length,unsigned char *dgst) {
    SHA256_CTX ctx;
    CALC_STRING_SHA(SHA256)
}

void _Sha::calc_stringSHA384(const char *content,int length,unsigned char *dgst) {
    SHA512_CTX ctx;
    CALC_STRING_SHA(SHA384)
}

void _Sha::calc_stringSHA512(const char *content,int length,unsigned char *dgst) {
    SHA512_CTX ctx;
    CALC_STRING_SHA(SHA512)
}

String _Sha::convert(unsigned char *content,int length) {
    char mdString[length*2+1];
    for (int i = 0; i < length; i++) {
        sprintf(&mdString[i*2], "%02x", (unsigned int)content[i]);        
    }
    return createString(&mdString[0]);
}

}
