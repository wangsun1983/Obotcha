#ifndef __OBOTCHA_RSA_HPP__
#define __OBOTCHA_RSA_HPP__

extern "C" {
#include "openssl/rsa.h"
#include "openssl/evp.h"
#include "openssl/ossl_typ.h"
}

#include "File.hpp"
#include "String.hpp"
#include "ByteArray.hpp"
#include "SecretKey.hpp"
#include "Cipher.hpp"

namespace obotcha {


DECLARE_SIMPLE_CLASS(Rsa) IMPLEMENTS(Cipher) {

public:
    ByteArray encrypt(ByteArray in);
    ByteArray decrypt(ByteArray in);

    enum RsaKeyType {
        RSA3 = RSA_3,
        RSAF4 = RSA_F4,
    };

private:
    int prikey_encrypt(const unsigned char *in, int in_len,
                   unsigned char **out, int &out_len);

    int pubkey_decrypt(const unsigned char *in, int in_len,
                           unsigned char **out, int &out_len);

    ByteArray pubkey_encrypt(ByteArray inputdata);
 
    ByteArray prikey_decrypt(ByteArray inputdata);

    ByteArray doRsa(ByteArray in,int mode /*Decrypt/Encrypt*/);

};

}

#endif
