#ifndef __OBOTCHA_RSA_SECRET_KEY_HPP__
#define __OBOTCHA_RSA_SECRET_KEY_HPP__

extern "C" {
#include "openssl/rsa.h"
#include "openssl/evp.h"
#include "openssl/ossl_typ.h"
}

#include "File.hpp"
#include "String.hpp"
#include "ByteArray.hpp"
#include "Cipher.hpp"

namespace obotcha {

/*
PKCS#1
-----BEGIN RSA PUBLIC KEY----- or -----BEGIN RSA PRIVATE KEY-----
BASE64 ENCODED DATA
-----END RSA PUBLIC KEY----- or -----BEGIN RSA PRIVATE KEY-----



PKCS#8
-----BEGIN PUBLIC KEY----- or -----BEGIN PRIVATE KEY-----
BASE64 ENCODED DATA
-----END PUBLIC KEY----- or -----BEGIN PRIVATE KEY-----
*/
class _Rsa;

DECLARE_SIMPLE_CLASS(RsaSecretKey) IMPLEMENTS(SecretKey){

public:
    enum KeyType {
        RsaPublicKey = 0,
        RsaPrivateKey,
    };

    friend class _Rsa;
    _RsaSecretKey();
    void * get();
    int loadEncryptKey(String path);
    int loadDecryptKey(String path);
    int generate(String decKeyFile,String encKeyFile,ArrayList<String>params);
    ~_RsaSecretKey();

private:
    RSA *mRsaKey;
    int mKeyType;

    const static String PKCS1PublicKeyTag;
    const static String PKCS1PrivateKeyTag;
    const static String PKCS8PublicKeyTag;
    const static String PKCS8PrivateKeyTag;

    enum PKCSKeyType {
        PKCS1PublicKey = 0,
        PKCS1PrivateKey,
        PKCS8PublicKey,
        PKCS8PrivateKey,
    };

    int getKeyType();

    int getPaddingType(String);
};

}
#endif
