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

    String encrypt(String);
    String decrypt(String);

private:
    RSA *mPubRsaKey;
    RSA *mPrivRsaKey;

    // 私钥加密函数
    int prikey_encrypt(const unsigned char *in, int in_len,
                   unsigned char **out, int &out_len);

    // 公钥解密函数，返回解密后的数据长度
    int pubkey_decrypt(const unsigned char *in, int in_len,
                           unsigned char **out, int &out_len);

    // 公钥加密函数
    int pubkey_encrypt(const unsigned char *in, int in_len,
                           unsigned char **out, int &out_len);
 
    // 私钥解密函数，返回解密后的长度
    int prikey_decrypt(const unsigned char *in, int in_len,
                           unsigned char **out, int &out_len);

};

}

#endif
