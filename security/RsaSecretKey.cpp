extern "C" {
    #include "openssl/pem.h"
}

#include "RsaSecretKey.hpp"
#include "FileInputStream.hpp"
#include "Cipher.hpp"
#include "Rsa.hpp"
#include "Log.hpp"
#include "Inspect.hpp"

namespace obotcha {

const String _RsaSecretKey::PKCS1PublicKeyTag = createString("BEGIN RSA PUBLIC KEY");
const String _RsaSecretKey::PKCS1PrivateKeyTag = createString("BEGIN RSA PRIVATE KEY");
const String _RsaSecretKey::PKCS8PublicKeyTag = createString("BEGIN PUBLIC KEY");
const String _RsaSecretKey::PKCS8PrivateKeyTag = createString("BEGIN PRIVATE KEY");

_RsaSecretKey::_RsaSecretKey() {
    mRsaKey = nullptr;
    mKeyPaddingType = st(Cipher)::PKCS1Padding;
    mKeyMode = st(Cipher)::RSA3;
}

void * _RsaSecretKey::get() {
    return mRsaKey;
}
    
int _RsaSecretKey::loadEncryptKey(String path) {
    FileInputStream stream = createFileInputStream(path);
    stream->open();
    ByteArray inputData = stream->readAll();
    String content = inputData->toString();
    stream->close();
    BIO* bio = BIO_new_mem_buf((void*)inputData->toValue(), inputData->size() ) ; // -1: assume string is null terminated
    if(bio == nullptr) {
        BIO_free(bio);
        return -1;
    }
    BIO_set_flags( bio, BIO_FLAGS_BASE64_NO_NL ) ; // NO NL

    mKeyPaddingType = getPaddingType(content);
    switch(mKeyPaddingType) {
        case PKCS1PublicKey:
            mRsaKey = PEM_read_bio_RSAPublicKey( bio, nullptr, nullptr, nullptr ) ;
        break;

        case PKCS8PublicKey:
            mRsaKey = PEM_read_bio_RSA_PUBKEY(bio, nullptr, nullptr, nullptr);
        break;

        default:
            break;
    }

    BIO_free(bio);
    return (mRsaKey == nullptr)?-1:0;
}

int _RsaSecretKey::loadDecryptKey(String path) {
    FileInputStream stream = createFileInputStream(path);
    stream->open();
    ByteArray inputData = stream->readAll();
    String content = inputData->toString();
    stream->close();
    BIO* bio = BIO_new_mem_buf((void*)inputData->toValue(), inputData->size()) ; // -1: assume string is null terminated
    if(bio == nullptr) {
        return -1;
    }
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL) ; // NO NL
    mKeyPaddingType = getPaddingType(content);
    switch(mKeyPaddingType) {
        case PKCS1PrivateKey:
            mRsaKey = PEM_read_bio_RSAPrivateKey( bio, nullptr, nullptr, nullptr ) ;
        break;

        default:
            break;
    }

    BIO_free(bio);

    return (mRsaKey == nullptr)?-1:0;
}

//rsa keytype/rsa key headtype
int _RsaSecretKey::generate(String decKeyFile,String encKeyFile,ArrayList<String>params) {
    RSA *keypair = RSA_new();
    BIGNUM* e = BN_new();

    int result = -1;
    switch(mKeyMode) {
        case st(Cipher)::RSA3:
            result = BN_set_word(e,RSA_3);
        break;

        case st(Cipher)::RSAF4:
            result = BN_set_word(e,RSA_F4);
            break;
    }
    
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
    switch(mKeyPaddingType) {
        case st(Cipher)::PKCS8Padding:
            result = PEM_write_bio_RSA_PUBKEY(bp_public, keypair);
        break;

        case st(Cipher)::PKCS1Padding:
        case st(Cipher)::OAEPPadding:
        case st(Cipher)::PSSPadding:
            result = PEM_write_bio_RSAPublicKey(bp_public, keypair);
        break;
    }

    Inspect(result != 1,-1);
 
    File privFile = createFile(decKeyFile);
    if(!privFile->exists()) {
        privFile->createNewFile();
    }

    // 3. save private key
    BIO *bp_private = BIO_new_file(privFile->getAbsolutePath()->toChars(), "w+");
    result = PEM_write_bio_RSAPrivateKey(bp_private, keypair, nullptr, nullptr, 0, nullptr, nullptr);
    // 4. free
    BIO_free_all(bp_public);
    BIO_free_all(bp_private);
    RSA_free(keypair);
    BN_free(e);
    return 0;
}

int _RsaSecretKey::getPaddingType(String content) {
    if(content->containsIgnoreCase(PKCS1PublicKeyTag)) {
        return PKCS1PublicKey;
    } else if(content->containsIgnoreCase(PKCS1PrivateKeyTag)) {
        return PKCS1PrivateKey;
    } else if(content->containsIgnoreCase(PKCS8PublicKeyTag)) {
        return PKCS8PublicKey;
    } else if(content->containsIgnoreCase(PKCS8PrivateKeyTag)) {
        return PKCS8PrivateKey;
    }
    return -1;
}

int _RsaSecretKey::getKeyType() {
    if(mKeyPaddingType == PKCS1PublicKey || mKeyPaddingType == PKCS8PublicKey) {
        return RsaPublicKey;
    } else if(mKeyPaddingType == PKCS1PrivateKey || mKeyPaddingType == PKCS8PrivateKey) {
        return RsaPrivateKey;
    }

    return -1;
}

void _RsaSecretKey::setKeyPaddingType(int padding) {
    this->mKeyPaddingType = padding;
}

void _RsaSecretKey::setMode(int mode) {
    this->mKeyMode = mode;
}

_RsaSecretKey::~_RsaSecretKey() {
    if(mRsaKey != nullptr) {
        RSA_free(mRsaKey);
        mRsaKey = nullptr;
    }
}



}
