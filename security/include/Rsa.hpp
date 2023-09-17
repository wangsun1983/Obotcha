#ifndef __OBOTCHA_RSA_HPP__
#define __OBOTCHA_RSA_HPP__

extern "C" {
#include "openssl/rsa.h"
#include "openssl/evp.h"
#include "openssl/ossl_typ.h"
}

#include "Object.hpp"
#include "ByteArray.hpp"
#include "Cipher.hpp"

namespace obotcha {

DECLARE_CLASS(Rsa) IMPLEMENTS(Cipher) {

public:
    ByteArray encryptContent(ByteArray in) override;
    ByteArray decryptContent(ByteArray in) override;

private:
    int prikey_encrypt(const unsigned char *in, int in_len,
                   unsigned char **out, int &out_len);

    int pubkey_decrypt(const unsigned char *in, int in_len,
                           unsigned char **out, int &out_len);

    ByteArray pubkey_encrypt(ByteArray inputdata);
 
    ByteArray prikey_decrypt(ByteArray inputdata);

    ByteArray doRsa(ByteArray in,st(Cipher)::Mode mode /*Decrypt/Encrypt*/);

};

}

#endif
