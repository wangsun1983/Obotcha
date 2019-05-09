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

void _Rsa::genKey(String pubkey,String privkey,int keytype) {
    
    RSA *keypair = RSA_new();
    BIGNUM* e = BN_new();
    int result = BN_set_word(e,keytype);
    if(result != 1) {
        //TODO
    }

    result = RSA_generate_key_ex(keypair,1024, e, NULL);

    File pubFile = createFile(pubkey);
    if(!pubFile->exists()) {
        pubFile->createNewFile();
    }

     // 2. save public key
    BIO *bp_public = BIO_new_file(pubFile->getAbsolutePath()->toChars(), "w+");
    result = PEM_write_bio_RSAPublicKey(bp_public, keypair);
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
    genKey(pubkey,privkey,RSA_F4);
}

void _Rsa::loadPrivateKey(String path) {


}

void _Rsa::loadPublicKey(String path) {

    FileInputStream inputStream = createFileInputStream(path);
    inputStream->open();
    ByteArray inputData = inputStream->readAll();
    printf("load pub key is %s \n",inputData->toValue());

    BIO* bio = BIO_new_mem_buf((void*)inputData->toValue(), -1 ) ; // -1: assume string is null terminated
    if(bio == nullptr) {
        printf("bio fail \n");
    }
    
    BIO_set_flags( bio, BIO_FLAGS_BASE64_NO_NL ) ; // NO NL

    // Load the RSA key from the BIO
    RSA* mPubRsaKey = PEM_read_bio_RSA_PUBKEY( bio, NULL, NULL, NULL ) ;
    if(!mPubRsaKey) {
        //TODO
        printf("load public key error \n");
    }

    BIO_free(bio);
    inputStream->close();
}

}
