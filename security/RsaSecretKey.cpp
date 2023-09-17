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

std::any _RsaSecretKey::get() {
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

    mPkcsType = getPkcsType(content);
    switch(mPkcsType) {
        case PKCSType::PKCS1PublicKey:
            mRsaKey = PEM_read_bio_RSAPublicKey( bio, nullptr, nullptr, nullptr ) ;
        break;

        case PKCSType::PKCS8PublicKey:
            mRsaKey = PEM_read_bio_RSA_PUBKEY(bio, nullptr, nullptr, nullptr);
        break;

        default:
            LOG(ERROR)<<"RsaSecretKey loadEncryptKey,unknow paddingType:"<<static_cast<int>(mKeyPaddingType);
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
    mPkcsType = getPkcsType(content);
    if(mPkcsType == PKCSType::PKCS1PrivateKey) {
        mRsaKey = PEM_read_bio_RSAPrivateKey( bio, nullptr, nullptr, nullptr ) ;
    } else {
        LOG(ERROR)<<"RsaSecretKey loadDecryptKey,unknow paddingType:"<<static_cast<int>(mKeyPaddingType);
    }
    BIO_free(bio);

    return (mRsaKey == nullptr)?-1:0;
}

//rsa keytype/rsa key headtype
int _RsaSecretKey::generate(String decKeyFile,String encKeyFile,ArrayList<String>params) {
    RSA *keypair = RSA_new();
    BIGNUM* e = BN_new();

    int result = -1;
    switch(mPattern) {
        case st(Cipher)::Pattern::RSA3:
            result = BN_set_word(e,RSA_3);
        break;

        case st(Cipher)::Pattern::RSAF4:
            result = BN_set_word(e,RSA_F4);
        break;

        default:
            LOG(ERROR)<<"RsaSecretKey generate,unknow keymode:"<<static_cast<int>(mPattern);
        break;
    }
    
    if(result != 1) {
        LOG(ERROR)<<"Rsa secret ky:BN_set_word fail";
        return -1;
    }

    result = RSA_generate_key_ex(keypair,2048, e, nullptr);
    File pubFile = createFile(encKeyFile);
    if(!pubFile->exists()) {
        pubFile->createNewFile();
    }

     // 2. save public key
    BIO *bp_public = BIO_new_file(pubFile->getAbsolutePath()->toChars(), "w+");
    switch(mKeyPaddingType) {
        case st(Cipher)::Padding::PKCS8:
            result = PEM_write_bio_RSA_PUBKEY(bp_public, keypair);
        break;

        case st(Cipher)::Padding::PKCS1:
        case st(Cipher)::Padding::OAEP:
        case st(Cipher)::Padding::PSS:
            result = PEM_write_bio_RSAPublicKey(bp_public, keypair);
        break;

        default:
            LOG(ERROR)<<"RsaSecretKey generate,unknow padding type:"<<static_cast<int>(mKeyPaddingType);
        break;
    }

    Inspect(result != 1,-1)
 
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
    return (result <= 0)?-1:0;
}

_RsaSecretKey::PKCSType _RsaSecretKey::getPkcsType(String content) const {
    if(content->containsIgnoreCase(PKCS1PublicKeyTag)) {
        return _RsaSecretKey::PKCSType::PKCS1PublicKey;
    } else if(content->containsIgnoreCase(PKCS1PrivateKeyTag)) {
        return _RsaSecretKey::PKCSType::PKCS1PrivateKey;
    } else if(content->containsIgnoreCase(PKCS8PublicKeyTag)) {
        return _RsaSecretKey::PKCSType::PKCS8PublicKey;
    } else if(content->containsIgnoreCase(PKCS8PrivateKeyTag)) {
        return _RsaSecretKey::PKCSType::PKCS8PrivateKey;
    }
    return _RsaSecretKey::PKCSType::Unknow;
}

int _RsaSecretKey::getKeyType() const {
    if(mPkcsType == PKCSType::PKCS1PublicKey || mPkcsType == PKCSType::PKCS8PublicKey) {
        return RsaPublicKey;
    } else if(mPkcsType == PKCSType::PKCS1PrivateKey || mPkcsType == PKCSType::PKCS8PrivateKey) {
        return RsaPrivateKey;
    }

    return -1;
}

void _RsaSecretKey::setKeyPaddingType(st(Cipher)::Padding padding) {
    this->mKeyPaddingType = padding;
}

void _RsaSecretKey::setKeyPattern(st(Cipher)::Pattern pattern) {
    this->mPattern = pattern;
}

_RsaSecretKey::~_RsaSecretKey() {
    if(mRsaKey != nullptr) {
        RSA_free(mRsaKey);
        mRsaKey = nullptr;
    }
}

}
