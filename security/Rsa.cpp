#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Rsa.hpp"
#include "File.hpp"
#include "FileInputStream.hpp"

extern "C" {
#include "openssl/pem.h"
}

namespace obotcha {


ByteArray _Rsa::decrypt(ByteArray content) {
    int length = 0;
    unsigned char *output = nullptr;
    int size = prikey_decrypt((const unsigned char*)content->toValue(),content->size(),&output,length);
    ByteArray result = createByteArray(output,length);
    if(output != nullptr) {
        free(output);
    }

    return result;
}

ByteArray _Rsa::encrypt(ByteArray content) {
    int length = 0;
    unsigned char *output = nullptr;
    printf("encrypt content is %s \n",content->toString()->toChars());
    int size = pubkey_encrypt((const unsigned char*)content->toValue(),content->size(),&output,length);
    ByteArray result = createByteArray(output,length);
    if(output != nullptr) {
        free(output);
    }

    return result;
}

int _Rsa::prikey_encrypt(const unsigned char *in, int in_len,
                   unsigned char **out, int &out_len)
{
    out_len =  RSA_size((const RSA*)getSecretKey()->get());
    *out =  (unsigned char *)malloc(out_len);
    if(NULL == *out)
    {
        return -1;
    }
    memset((void *)*out, 0, out_len);
    switch(getPadding()) {
        case PKCS1Padding:
        return RSA_private_encrypt(in_len, in, *out, (RSA*)getSecretKey()->get(), RSA_PKCS1_PADDING);
        break;
    }

    return -1;
}


int _Rsa::pubkey_decrypt(const unsigned char *in, int in_len,
                           unsigned char **out, int &out_len)
{
    out_len =  RSA_size((const RSA*)getSecretKey()->get());
    *out =  (unsigned char *)malloc(out_len);
    if(nullptr == *out) {
        return -1;
    }
    memset((void *)*out, 0, out_len);
    switch(getPadding()) {
        case PKCS1Padding:
        return RSA_public_decrypt(in_len, in, *out, (RSA*)getSecretKey()->get(), RSA_PKCS1_PADDING);
    }
    return -1;
}

int _Rsa::pubkey_encrypt(const unsigned char *in, int in_len,
                           unsigned char **out, int &out_len)
{
    const RSA * key = (const RSA*)getSecretKey()->get();
    out_len =  RSA_size(key);
    *out =  (unsigned char *)malloc(out_len + 1);
    if(nullptr == *out) {
        return -1;
    }

    memset((void *)*out, 0, out_len + 1);
    switch(getPadding()) {
        case PKCS1Padding:
        return RSA_public_encrypt(in_len, in, *out, (RSA*)getSecretKey()->get(), RSA_PKCS1_PADDING);
    }
    return -1;
}
 

int _Rsa::prikey_decrypt(const unsigned char *in, int in_len,
                           unsigned char **out, int &out_len)
{
    OpenSSL_add_all_algorithms();  
    out_len =  RSA_size((const RSA*)getSecretKey()->get());
    *out =  (unsigned char *)malloc(out_len + 1);
    if(nullptr == *out) {
        return -1;
    }
    memset((void *)*out, 0, out_len + 1);
    switch(getPadding()) {
        case PKCS1Padding:
        return RSA_private_decrypt(in_len, in, *out, (RSA*)getSecretKey()->get(), getPadding());
    }
 
    return -1;
}

}
