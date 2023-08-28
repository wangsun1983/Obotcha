#ifndef __OBOTCHA_AES_SECRET_KEY_HPP__
#define __OBOTCHA_AES_SECRET_KEY_HPP__

extern "C" {
#include "openssl/aes.h"
}

#include "Object.hpp"
#include "ArrayList.hpp"
#include "SecretKey.hpp"

namespace obotcha {

DECLARE_CLASS(AesSecretKey) IMPLEMENTS(SecretKey) {
public:
    std::any get();
    int loadEncryptKey(String path);
    int loadDecryptKey(String path);
    int generate(String decKeyFile,String encKeyFile,ArrayList<String>params);
    void setType(int);

private:
    AES_KEY mKey;
    int loadKey(String path);
    int genKey(String content,AES_KEY *encrypt,AES_KEY *decrypt) const;
    int mType;
    int getKeyLength() const;
    int keyCheck(String) const;
};

}
#endif
