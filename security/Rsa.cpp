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


_Rsa::_Rsa() {
    //TODO
}

void _Rsa::genKey(String pubkey,String privkey,int keytype,int keyheadtype) {
    
    RSA *keypair = RSA_new();
    BIGNUM* e = BN_new();
    int result = BN_set_word(e,keytype);
    if(result != 1) {
        //TODO
    }

    result = RSA_generate_key_ex(keypair,2048, e, NULL);

    File pubFile = createFile(pubkey);
    if(!pubFile->exists()) {
        pubFile->createNewFile();
    }

     // 2. save public key
    BIO *bp_public = BIO_new_file(pubFile->getAbsolutePath()->toChars(), "w+");
    switch(keyheadtype) {
        case PKCS_1:
            result = PEM_write_bio_RSA_PUBKEY(bp_public, keypair);
        break;

        case PKCS_8:
            result = PEM_write_bio_RSAPublicKey(bp_public, keypair);
        break;
    }

    if(result != 1){
        return;
    }
 
    File privFile = createFile(privkey);
    if(!privFile->exists()) {
        privFile->createNewFile();
    }

    // 3. save private key
    BIO *bp_private = BIO_new_file(privFile->getAbsolutePath()->toChars(), "w+");
    result = PEM_write_bio_RSAPrivateKey(bp_private, keypair, NULL, NULL, 0, NULL, NULL);
    // 4. free
    BIO_free_all(bp_public);
    BIO_free_all(bp_private);
    RSA_free(keypair);
    BN_free(e);
}

void _Rsa::genKey(String pubkey,String privkey) {
    genKey(pubkey,privkey,RSA_F4,PKCS_1);
}

void _Rsa::loadPrivateKey(String path) {
    FileInputStream inputStream = createFileInputStream(path);
    inputStream->open();
    ByteArray inputData = inputStream->readAll();
    printf("load private key is %s \n",inputData->toValue());

    BIO* bio = BIO_new_mem_buf((void*)inputData->toValue(), -1 ) ; // -1: assume string is null terminated
    if(bio == nullptr) {
        printf("bio fail \n");
    }
    
    BIO_set_flags( bio, BIO_FLAGS_BASE64_NO_NL ) ; // NO NL

    // Load the RSA key from the BIO
    //PEM_read_bio_RSAPublicKey =>PKCS#1(-----BEGIN RSA PUBLIC KEY-----)
    //PEM_read_bio_RSA_PUBKEY =>PKCS#8(-----BEGIN PUBLIC KEY-----)
    mPrivRsaKey = PEM_read_bio_RSAPrivateKey( bio, NULL, NULL, NULL ) ;
    if(!mPrivRsaKey) {
        //TODO
        printf("load private key fail \n");
        goto freeall;
        
    }

freeall:
    BIO_free(bio);
    inputStream->close();

}

void _Rsa::loadPublicKey(String path) {

    File keyFile = createFile(path);
    long int size = keyFile->length();

    FileInputStream inputStream = createFileInputStream(path);
    inputStream->open();

    ByteArray inputData = createByteArray(size + 1);
    inputStream->readAll(inputData);

    printf("load pub key is %s \n",inputData->toValue());

    BIO* bio = BIO_new_mem_buf((void*)inputData->toValue(), -1 ) ; // -1: assume string is null terminated
    if(bio == nullptr) {
        printf("bio fail \n");
    }
    
    BIO_set_flags( bio, BIO_FLAGS_BASE64_NO_NL ) ; // NO NL

    // Load the RSA key from the BIO
    //PEM_read_bio_RSAPublicKey =>PKCS#1(-----BEGIN RSA PUBLIC KEY-----)
    //PEM_read_bio_RSA_PUBKEY =>PKCS#8(-----BEGIN PUBLIC KEY-----)
    mPubRsaKey = PEM_read_bio_RSAPublicKey( bio, NULL, NULL, NULL ) ;
    if(!mPubRsaKey) {
        //TODO
        printf("load pub key fail \n");
        BIO_free(bio);
        BIO* bio = BIO_new_mem_buf((void*)inputData->toValue(), -1 ) ;
        BIO_set_flags( bio, BIO_FLAGS_BASE64_NO_NL ) ; // NO NL
        mPubRsaKey = PEM_read_bio_RSA_PUBKEY(bio, NULL, NULL, NULL);
        if(!mPubRsaKey) {
            printf("load pub key fail again\n");
            goto freeall;
        }
    }

freeall:
    BIO_free(bio);
    inputStream->close();
}

ByteArray _Rsa::encrypt(String content) {
    //String output = createString();
    int length = 0;
    unsigned char *output = nullptr;
    pubkey_encrypt((const unsigned char*)content->toChars(),content->size(),&output,length);
    printf("encrypt output is %s,size is %d \n",output,length);
    //String result = createString((char *)output);
    //printf("encrypt result is %s \n",result->toChars());
    //return result;
    ByteArray result = createByteArray((char *)output,length);
    if(output != nullptr) {
        free(output);
    }

    return result;
}

ByteArray _Rsa::decrypt(ByteArray content) {
    //String output = createString();
    int length = 0;
    unsigned char *output = nullptr;
    printf("decrypt content is %s,size is %d \n",content->toValue(),content->size());
    int size = prikey_decrypt((const unsigned char*)content->toValue(),content->size(),&output,length);
    printf("decrypt output is %s,size is %d \n",(char *)output,size);
    //return createString(output);
    ByteArray result = createByteArray((char *)output,length);
    if(output != nullptr) {
        free(output);
    }

    return result;
}

int _Rsa::prikey_encrypt(const unsigned char *in, int in_len,
                   unsigned char **out, int &out_len)
{
    out_len =  RSA_size(mPrivRsaKey);
    *out =  (unsigned char *)malloc(out_len);
    if(NULL == *out)
    {
        
        printf("prikey_encrypt:malloc error!\n");
        return -1;
    }
    memset((void *)*out, 0, out_len);
 
    printf("prikey_encrypt:Begin RSA_private_encrypt ...\n");
    int ret =  RSA_private_encrypt(in_len, in, *out, mPrivRsaKey, RSA_PKCS1_PADDING);
    //RSA_public_decrypt(flen, encData, decData, r,  RSA_NO_PADDING);
 
    return ret;
}


int _Rsa::pubkey_decrypt(const unsigned char *in, int in_len,
                           unsigned char **out, int &out_len)
{
    out_len =  RSA_size(mPubRsaKey);
    *out =  (unsigned char *)malloc(out_len);
    if(nullptr == *out) {
        printf("pubkey_decrypt:malloc error!\n");
        return -1;
    }
    memset((void *)*out, 0, out_len);
 
    printf("pubkey_decrypt:Begin RSA_public_decrypt ...\n");
    int ret =  RSA_public_decrypt(in_len, in, *out, mPubRsaKey, RSA_PKCS1_PADDING);
 
    return ret;
}

int _Rsa::pubkey_encrypt(const unsigned char *in, int in_len,
                           unsigned char **out, int &out_len)
{
    out_len =  RSA_size(mPubRsaKey);
    *out =  (unsigned char *)malloc(out_len + 1);
    if(nullptr == *out) {
        printf("pubkey_encrypt:malloc error!\n");
        return -1;
    }

    memset((void *)*out, 0, out_len + 1);
 
    printf("pubkey_encrypt:Begin RSA_public_encrypt ...\n");
    int ret =  RSA_public_encrypt(in_len, in, *out, mPubRsaKey, RSA_PKCS1_PADDING/*RSA_NO_PADDING*/);
 
 
    return ret;
}
 

int _Rsa::prikey_decrypt(const unsigned char *in, int in_len,
                           unsigned char **out, int &out_len)
{
    OpenSSL_add_all_algorithms();  
    out_len =  RSA_size(mPrivRsaKey);
    *out =  (unsigned char *)malloc(out_len + 1);
    if(nullptr == *out)
    {
        printf("prikey_decrypt:malloc error!\n");
        return -1;
    }
    memset((void *)*out, 0, out_len + 1);
 
    printf("prikey_decrypt:Begin RSA_private_decrypt ...\n");
    int ret =  RSA_private_decrypt(in_len, in, *out, mPrivRsaKey, RSA_PKCS1_PADDING);
 
    return ret;
}

}
