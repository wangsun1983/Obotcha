#ifndef __OBOTCHA_AES_HPP__
#define __OBOTCHA_AES_HPP__

extern "C" {
#include "openssl/aes.h"
}

#include "Object.hpp"
#include "File.hpp"
#include "String.hpp"
#include "ByteArray.hpp"
#include "Cipher.hpp"

namespace obotcha {

DECLARE_CLASS(Aes) IMPLEMENTS(Cipher) {

public:   
    int genKey(String decKeyFile,String encKeyFile,ArrayList<String>params);
    
    ByteArray encryptContent(ByteArray in) override;

    ByteArray decryptContent(ByteArray in) override;

private:

    int _genKey(String content,AES_KEY *encrypt,AES_KEY *decrypt);

    ByteArray _aesECB(ByteArray data);

    ByteArray _aesCBC(ByteArray data);

    ByteArray _aesCFB1(ByteArray in);

    ByteArray _aesCFB8(ByteArray in);

    ByteArray _aesCFB128(ByteArray in);

    ByteArray _aesOFB128(ByteArray in);
};

}

#endif
