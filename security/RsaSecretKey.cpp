extern "C" {
    #include "openssl/pem.h"
}

#include "RsaSecretKey.hpp"
#include "FileInputStream.hpp"
#include "Cipher.hpp"
#include "Rsa.hpp"
#include "Log.hpp"

namespace obotcha {

const String _RsaSecretKey::PKCS1PublicKeyTag = createString("BEGIN RSA PUBLIC KEY");
const String _RsaSecretKey::PKCS1PrivateKeyTag = createString("BEGIN RSA PRIVATE KEY");
const String _RsaSecretKey::PKCS8PublicKeyTag = createString("BEGIN PUBLIC KEY");
const String _RsaSecretKey::PKCS8PrivateKeyTag = createString("BEGIN PRIVATE KEY");

_RsaSecretKey::_RsaSecretKey() {
    mRsaKey = nullptr;
}

void * _RsaSecretKey::get() {
    return mRsaKey;
}
    
int _RsaSecretKey::loadEncryptKey(String path) {
    printf("RSA secretkey load start path is %s \n",path->toChars());
    FileInputStream stream = createFileInputStream(path);
    stream->open();
    ByteArray inputData = stream->readAll();
    printf("loadEncryptKey inputdata size is %d \n",inputData->size());
    String content = inputData->toString();
    printf("content is %s \n",content->toChars());
    stream->close();
    BIO* bio = BIO_new_mem_buf((void*)inputData->toValue(), -1 ) ; // -1: assume string is null terminated
    if(bio == nullptr) {
        return -1;
    }
    printf("RSA secretkey load trace1 \n");
    BIO_set_flags( bio, BIO_FLAGS_BASE64_NO_NL ) ; // NO NL

    printf("RSA secretkey load trace2 \n");
    switch(getPaddingType(content)) {
        case PKCS1PublicKey:
        printf("RSA secretkey load trace3 \n");
            mRsaKey = PEM_read_bio_RSAPublicKey( bio, NULL, NULL, NULL ) ;
        break;

        case PKCS8PublicKey:
        printf("RSA secretkey load trace4 \n");
            mRsaKey = PEM_read_bio_RSA_PUBKEY(bio, NULL, NULL, NULL);
        break;

        default:
        printf("RSA secretkey load trace5 \n");
            return -1;
    }

    if(mRsaKey == nullptr) {
        return -1;
    }
    printf("RSA secretkey load trace6 \n");
    return 0;
}

int _RsaSecretKey::loadDecryptKey(String path) {
    printf("loadDecryptKey path is %s \n",path->toChars());
    FileInputStream stream = createFileInputStream(path);
    stream->open();
    ByteArray inputData = stream->readAll();
    String content = inputData->toString();
    stream->close();
    BIO* bio = BIO_new_mem_buf((void*)inputData->toValue(), -1 ) ; // -1: assume string is null terminated
    if(bio == nullptr) {
        return -1;
    }
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL) ; // NO NL


    switch(getPaddingType(content)) {
        case PKCS1PrivateKey:
            mRsaKey = PEM_read_bio_RSAPrivateKey( bio, NULL, NULL, NULL ) ;
        break;

        default:
            return -1;
    }

    if(mRsaKey == nullptr) {
        return -1;
    }
    
    return 0;
}

//rsa keytype/rsa key headtype
int _RsaSecretKey::generate(String decKeyFile,String encKeyFile,ArrayList<String>params) {
    int keytype = st(Rsa)::RSA3;
    int keyHeadType = st(Cipher)::PKCS1Padding;

    if(params->size() == 2) {
        String keytpeString = params->get(0);
        if(keytpeString->equals("RSAF4")) {
            keytype = st(Rsa)::RSAF4;
        }

        String keyHeadTypeString = params->get(1);
        if(keytpeString->equals("PKCS1Padding")) {
            keyHeadType = st(Cipher)::PKCS1Padding;
        } else if(keytpeString->equals("PKCS8Padding")) {
            keyHeadType = st(Cipher)::PKCS8Padding;
        }
    }

    RSA *keypair = RSA_new();
    BIGNUM* e = BN_new();
    int result = BN_set_word(e,keytype);
    if(result != 1) {
        LOG(ERROR)<<"Rsa secret ky:BN_set_word fail";
        return -1;
    }

    result = RSA_generate_key_ex(keypair,2048, e, NULL);

    File pubFile = createFile(encKeyFile);
    if(!pubFile->exists()) {
        pubFile->createNewFile();
    }

     // 2. save public key
    BIO *bp_public = BIO_new_file(pubFile->getAbsolutePath()->toChars(), "w+");
    switch(keyHeadType) {
        case st(Cipher)::PKCS1Padding:
            result = PEM_write_bio_RSA_PUBKEY(bp_public, keypair);
        break;

        case st(Cipher)::PKCS8Padding:
            result = PEM_write_bio_RSAPublicKey(bp_public, keypair);
        break;
    }

    if(result != 1){
        return -1;
    }
 
    File privFile = createFile(decKeyFile);
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
    return 0;
}

int _RsaSecretKey::getPaddingType(String content) {
    printf("content is %s \n",content->toChars());
    if(content->containsIgnoreCase(PKCS1PublicKeyTag)) {
        printf("padding type 1 \n");
        return PKCS1PublicKey;
    } else if(content->containsIgnoreCase(PKCS1PrivateKeyTag)) {
        printf("padding type 2 \n");
        return PKCS1PrivateKey;
    } else if(content->containsIgnoreCase(PKCS8PublicKeyTag)) {
        printf("padding type 3 \n");
        return PKCS8PublicKey;
    } else if(content->containsIgnoreCase(PKCS8PrivateKeyTag)) {
        printf("padding type 4 \n");
        return PKCS8PrivateKey;
    }
    return -1;
}

_RsaSecretKey::~_RsaSecretKey() {
    if(mRsaKey != nullptr) {
        RSA_free(mRsaKey);
        mRsaKey = nullptr;
    }
}



}
