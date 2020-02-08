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
    unsigned char *encdata;
    int length;

    switch(mType) {
        case SHA_1: {
            unsigned char encryptData[SHA_DIGEST_LENGTH] = {0};
            calc_stringSHA1((char *)data->toValue(),data->size(),encryptData);
            encdata = encryptData;
            length = SHA_DIGEST_LENGTH;
        }
        break;

        case SHA_224: {
            unsigned char encryptData[SHA224_DIGEST_LENGTH] = {0};
            calc_stringSHA224((char *)data->toValue(),data->size(),encryptData);
            encdata = encryptData;
            length = SHA224_DIGEST_LENGTH;
        }
        break;

        case SHA_256: {
            unsigned char encryptData[SHA256_DIGEST_LENGTH] = {0};
            calc_stringSHA256((char *)data->toValue(),data->size(),encryptData);
            encdata = encryptData;
            length = SHA256_DIGEST_LENGTH;
        }
        break;

        case SHA_384: {
            unsigned char encryptData[SHA384_DIGEST_LENGTH] = {0};
            calc_stringSHA384((char *)data->toValue(),data->size(),encryptData);
            encdata = encryptData;
            length = SHA384_DIGEST_LENGTH;
        }
        break;

        case SHA_512: {
            unsigned char encryptData[SHA512_DIGEST_LENGTH] = {0};
            calc_stringSHA512((char *)data->toValue(),data->size(),encryptData);
            encdata = encryptData;
            length = SHA512_DIGEST_LENGTH;
        }
        break;
    }
    return createByteArray(encdata,length);
}

String _Sha::encrypt(File file) {
    unsigned char *encdata;
    int length;

    switch(mType) {
        case SHA_1: {
            unsigned char encryptData[SHA_DIGEST_LENGTH] = {0};
            calc_fileSHA1(file->getAbsolutePath()->toChars(),encryptData);
            encdata = encryptData;
            length = SHA_DIGEST_LENGTH;
        }
        break;

        case SHA_224: {
            unsigned char encryptData[SHA224_DIGEST_LENGTH] = {0};
            calc_fileSHA224(file->getAbsolutePath()->toChars(),encryptData);
            encdata = encryptData;
            length = SHA224_DIGEST_LENGTH;
        }
        break;

        case SHA_256: {
            unsigned char encryptData[SHA256_DIGEST_LENGTH] = {0};
            calc_fileSHA256(file->getAbsolutePath()->toChars(),encryptData);
            encdata = encryptData;
            length = SHA256_DIGEST_LENGTH;
        }
        break;

        case SHA_384: {
            unsigned char encryptData[SHA384_DIGEST_LENGTH] = {0};
            calc_fileSHA384(file->getAbsolutePath()->toChars(),encryptData);
            encdata = encryptData;
            length = SHA384_DIGEST_LENGTH;
        }
        break;

        case SHA_512: {
            unsigned char encryptData[SHA512_DIGEST_LENGTH] = {0};
            calc_fileSHA512(file->getAbsolutePath()->toChars(),encryptData);
            encdata = encryptData;
            length = SHA512_DIGEST_LENGTH;
        }
        break;
    }

    return convert(encdata,length);
}

void _Sha::calc_fileSHA1(const char *filename,unsigned char *dgst) {

    SHA_CTX ctx;
    
    if (NULL == filename || NULL == dgst) {
        return;
    }

    SHA1_Init(&ctx);
    
    File file = createFile(filename);
    FileInputStream inputstream = createFileInputStream(file);
    inputstream->open();

    ByteArray content = inputstream->readAll();
    SHA1_Update(&ctx, content->toValue(), content->size());
    inputstream->close();
    
    SHA1_Final(dgst, &ctx);
}

void _Sha::calc_fileSHA224(const char *filename,unsigned char *dgst) {
    SHA256_CTX ctx;
    char buf[4096] = {0};
    int len = 0;

    if (NULL == filename || NULL == dgst) {
        return;
    }

    FILE *fp = fopen(filename, "rb");
    if (NULL == fp) {
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
        return;
    }

    FILE *fp = fopen(filename, "rb");
    if (NULL == fp) {
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
        return;
    }

    FILE *fp = fopen(filename, "rb");
    if (NULL == fp) {
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
        return;
    }

    FILE *fp = fopen(filename, "rb");

    if (NULL == fp) {
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
