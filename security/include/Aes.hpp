#ifndef __OBOTCHA_AES_HPP__
#define __OBOTCHA_AES_HPP__

#include "openssl/aes.h"

#include "File.hpp"
#include "String.hpp"
#include "ByteArray.hpp"
#include "Cipher.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Aes) IMPLEMENTS(Cipher) {

public:   
    int genKey(String decKeyFile,String encKeyFile,ArrayList<String>params);
    
    ByteArray encrypt(ByteArray in);

    ByteArray decrypt(ByteArray in);

private:

    int _genKey(String content,AES_KEY *encrypt,AES_KEY *decrypt);

    ByteArray _aesECB(ByteArray data);

    ByteArray _aesCBC(ByteArray data,unsigned char *ivec);
};

}

#endif
