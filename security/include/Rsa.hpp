#ifndef __RSA_HPP__
#define __RSA_HPP__

extern "C" {
#include "openssl/rsa.h"
#include "openssl/evp.h"
#include "openssl/ossl_typ.h"
}

#include "File.hpp"
#include "String.hpp"
#include "ByteArray.hpp"

namespace obotcha {

enum RsaMode {
    RsaEncrypt,
    RsaDecrypt,
};

enum RsaKeyType {
    RsaKeyTypeRSA3 = RSA_3,
    RsaKeyTypeRSAF4 = RSA_F4,
};

enum RsaKeyHeadType {
    PKCS_1,
    PKCS_8
};

DECLARE_SIMPLE_CLASS(Rsa) {

public:
    _Rsa();

    void genKey(String pubkey,String privkey,int keytype,int keyheadtype);
    void genKey(String pubkey,String privkey);

    void loadPrivateKey(String);
    void loadPublicKey(String);

    ByteArray encrypt(String);
    ByteArray decrypt(ByteArray);

private:
    RSA *mPubRsaKey;
    RSA *mPrivRsaKey;

    int prikey_encrypt(const unsigned char *in, int in_len,
                   unsigned char **out, int &out_len);

    int pubkey_decrypt(const unsigned char *in, int in_len,
                           unsigned char **out, int &out_len);

    int pubkey_encrypt(const unsigned char *in, int in_len,
                           unsigned char **out, int &out_len);
 
    int prikey_decrypt(const unsigned char *in, int in_len,
                           unsigned char **out, int &out_len);

};

}

#endif
