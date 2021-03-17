#ifndef __OBOTCHA_AES_SECRET_KEY_HPP__
#define __OBOTCHA_AES_SECRET_KEY_HPP__

#include "openssl/aes.h"
#include "StrongPointer.hpp"
#include "Object.hpp"
#include "ByteArray.hpp"
#include "File.hpp"
#include "SecretKey.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(AesSecretKey) IMPLEMENTS(SecretKey) {
public:
    void *get();
    int loadEncryptKey(String path);
    int loadDecryptKey(String path);
    int generate(String decKeyFile,String encKeyFile,ArrayList<String>params);

private:
    AES_KEY mKey;
    int loadKey(String path);
    int genKey(String content,AES_KEY *encrypt,AES_KEY *decrypt);
};

}
#endif
