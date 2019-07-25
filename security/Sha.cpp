#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>


#include "Sha.hpp"

namespace obotcha {

_Sha::_Sha(int type) {
    mType = type;
}

String _Sha::encrypt(String str) {
    unsigned char encryptData[SHA_DIGEST_LENGTH] = {0};
    switch(mType) {
        case AbstractSHA1:
            calc_stringSHA1(str->toChars(),str->size(),encryptData);
        break;

        case AbstractSHA224:
            calc_stringSHA224(str->toChars(),str->size(),encryptData);
        break;

        case AbstractSHA256:
            calc_stringSHA256(str->toChars(),str->size(),encryptData);
        break;

        case AbstractSHA384:
            calc_stringSHA384(str->toChars(),str->size(),encryptData);
        break;

        case AbstractSHA512:
            calc_stringSHA512(str->toChars(),str->size(),encryptData);
        break;
    }

    return convert(encryptData,SHA_DIGEST_LENGTH);
}

ByteArray _Sha::encryptRawData(ByteArray data) {
    unsigned char encryptData[SHA_DIGEST_LENGTH] = {0};
    printf("wangsl,encrypt raw data1 \n");
    switch(mType) {
        case AbstractSHA1:
            calc_stringSHA1(data->toValue(),data->size(),encryptData);
        break;

        case AbstractSHA224:
            calc_stringSHA224(data->toValue(),data->size(),encryptData);
        break;

        case AbstractSHA256:
            calc_stringSHA256(data->toValue(),data->size(),encryptData);
        break;

        case AbstractSHA384:
            calc_stringSHA384(data->toValue(),data->size(),encryptData);
        break;

        case AbstractSHA512:
            calc_stringSHA512(data->toValue(),data->size(),encryptData);
        break;
    }
    printf("wangsl,encrypt raw data2 \n");
    return createByteArray((char *)encryptData,SHA_DIGEST_LENGTH);
}

String _Sha::encrypt(File file) {
    unsigned char encryptData[SHA_DIGEST_LENGTH] = {0};
    switch(mType) {
        case AbstractSHA1:
            calc_fileSHA1(file->getAbsolutePath()->toChars(),encryptData);
        break;

        case AbstractSHA224:
            calc_fileSHA224(file->getAbsolutePath()->toChars(),encryptData);
        break;

        case AbstractSHA256:
            calc_fileSHA256(file->getAbsolutePath()->toChars(),encryptData);
        break;

        case AbstractSHA384:
            calc_fileSHA384(file->getAbsolutePath()->toChars(),encryptData);
        break;

        case AbstractSHA512:
            calc_fileSHA512(file->getAbsolutePath()->toChars(),encryptData);
        break;
    }

    return convert(encryptData,SHA_DIGEST_LENGTH);
}

void _Sha::calc_fileSHA1(const char *filename,unsigned char *dgst) {

    SHA_CTX ctx;
    char buf[4096] = {0};
    int len = 0;

    if (NULL == filename || NULL == dgst) {
        printf("Input error...\n");
        return;
    }

    FILE *fp = fopen(filename, "rb");
    if (NULL == fp) {
        printf("open file:%s error...\n", filename);
        return;
    }

    SHA1_Init(&ctx);
    
    while ((len = fread(buf, 1, 4096, fp)) > 0) {
        SHA1_Update(&ctx, buf, len);
        memset(buf, 0, len);
    }

    SHA1_Final(dgst, &ctx);

    fclose(fp);
}

void _Sha::calc_fileSHA224(const char *filename,unsigned char *dgst) {
    SHA256_CTX ctx;
    char buf[4096] = {0};
    int len = 0;

    if (NULL == filename || NULL == dgst) {
        printf("Input error...\n");
        return;
    }

    FILE *fp = fopen(filename, "rb");
    if (NULL == fp) {
        printf("open file:%s error...\n", filename);
        return;
    }

    SHA224_Init(&ctx);
    while ((len = fread(buf, 1, 4096, fp)) > 0) {
        SHA224_Update(&ctx, buf, len);
        memset(buf, 0, len);
    }

    SHA224_Final(dgst, &ctx);

    fclose(fp);
}

void _Sha::calc_fileSHA256(const char *filename,unsigned char *dgst) {
    SHA256_CTX ctx;
    char buf[4096] = {0};
    int len = 0;

    if (NULL == filename || NULL == dgst) {
        printf("Input error...\n");
        return;
    }

    FILE *fp = fopen(filename, "rb");
    if (NULL == fp) {
        printf("open file:%s error...\n", filename);
        return;
    }

    SHA256_Init(&ctx);
    
    while ((len = fread(buf, 1, 4096, fp)) > 0) {
        SHA256_Update(&ctx, buf, len);
        memset(buf, 0, len);
    }

    SHA256_Final(dgst, &ctx);

    fclose(fp);
}

void _Sha::calc_fileSHA384(const char *filename,unsigned char *dgst) {
    SHA512_CTX ctx;
    char buf[4096] = {0};
    int len = 0;

    if (NULL == filename || NULL == dgst) {
        printf("Input error...\n");
        return;
    }

    FILE *fp = fopen(filename, "rb");
    if (NULL == fp) {
        printf("open file:%s error...\n", filename);
        return;
    }

    SHA384_Init(&ctx);
    while ((len = fread(buf, 1, 4096, fp)) > 0) {
        SHA384_Update(&ctx, buf, len);
        memset(buf, 0, len);
    }

    SHA384_Final(dgst, &ctx);

    fclose(fp);
}

void _Sha::calc_fileSHA512(const char *filename,unsigned char *dgst) {
    SHA512_CTX ctx;
    char buf[4096] = {0};
    int len = 0;

    if (NULL == filename || NULL == dgst) {
        printf("Input error...\n");
        return;
    }

    FILE *fp = fopen(filename, "rb");

    if (NULL == fp) {
        printf("open file:%s error...\n", filename);
        return;
    }

    SHA512_Init(&ctx);
    
    while ((len = fread(buf, 1, 4096, fp)) > 0) {
        SHA512_Update(&ctx, buf, len);
        memset(buf, 0, len);
    }

    SHA512_Final(dgst, &ctx);
    fclose(fp);
}

void _Sha::calc_stringSHA1(const char *content,int length,unsigned char *dgst) {
    SHA_CTX ctx;

    if (NULL == content || NULL == dgst)
    {
        printf("Input error...\n");
        return;
    }

    SHA1_Init(&ctx);
    SHA1_Update(&ctx, content, length);
    SHA1_Final(dgst, &ctx);
}

void _Sha::calc_stringSHA224(const char *content,int length,unsigned char *dgst) {
    SHA256_CTX ctx;

    if (NULL == content || NULL == dgst)
    {
        printf("Input error...\n");
        return;
    }

    SHA224_Init(&ctx);
    SHA224_Update(&ctx, content, length);
    SHA224_Final(dgst, &ctx);
}

void _Sha::calc_stringSHA256(const char *content,int length,unsigned char *dgst) {
    SHA256_CTX ctx;

    if (NULL == content || NULL == dgst)
    {
        printf("Input error...\n");
        return;
    }

    SHA256_Init(&ctx);
    SHA256_Update(&ctx, content, length);
    SHA256_Final(dgst, &ctx);
}

void _Sha::calc_stringSHA384(const char *content,int length,unsigned char *dgst) {
    SHA512_CTX ctx;

    if (NULL == content || NULL == dgst)
    {
        printf("Input error...\n");
        return;
    }

    SHA384_Init(&ctx);
    SHA384_Update(&ctx, content, length);
    SHA384_Final(dgst, &ctx);
}

void _Sha::calc_stringSHA512(const char *content,int length,unsigned char *dgst) {
    SHA512_CTX ctx;

    if (NULL == content || NULL == dgst)
    {
        printf("Input error...\n");
        return;
    }

    SHA512_Init(&ctx);
    SHA512_Update(&ctx, content, length);
    SHA512_Final(dgst, &ctx);
}

String _Sha::convert(unsigned char *content,int length) {
    char mdString[length*2+1];
    for (int i = 0; i < length; i++) {
        sprintf(&mdString[i*2], "%02x", (unsigned int)content[i]);        
    }
    return createString(&mdString[0]);
}

}
