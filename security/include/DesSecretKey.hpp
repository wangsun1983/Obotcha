#ifndef __OBOTCHA_DES_SECRET_KEY_HPP__
#define __OBOTCHA_DES_SECRET_KEY_HPP__

extern "C" {
#include "openssl/des.h"
}

#include "Object.hpp"
#include "String.hpp"
#include "SecretKey.hpp"

namespace obotcha {

DECLARE_CLASS(DesSecretKey) IMPLEMENTS(SecretKey){

public:
    std::any get() override;
    int loadEncryptKey(String path) override;
    int loadDecryptKey(String path) override;
    int generate(String decKeyFile,String encKeyFile,ArrayList<String>params) override;

private:
    DES_cblock mKey;
    static const size_t DesKeySize;
    int loadKey(String path);
    int saveKey(String filepath,DES_cblock *block) const;

};

}
#endif
