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

DECLARE_SIMPLE_CLASS(Rsa) {

public:
    _Rsa();

    void genKey(String pubkey,String privkey,int keytype);
    void genKey(String pubkey,String privkey);

    void loadPrivateKey(String);
    void loadPublicKey(String);

private:
    RSA *mPubRsaKey;
    RSA *mPrivRsaKey;

};

}

#endif
