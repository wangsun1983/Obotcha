#ifndef __OBOTCHA_DES_SECRET_KEY_HPP__
#define __OBOTCHA_DES_SECRET_KEY_HPP__

#include "openssl/des.h"

#include "File.hpp"
#include "String.hpp"
#include "ByteArray.hpp"
#include "Cipher.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(DesSecretKey) IMPLEMENTS(SecretKey){

public:
    void * get();
    int loadEncryptKey(String path);
    int loadDecryptKey(String path);
    int generate(String decKeyFile,String encKeyFile,ArrayList<String>params);

private:
    DES_cblock mKey;
    static const int DesKeySize;
    int loadKey(String path);
    int saveKey(String filepath,DES_cblock *block);

};

}
#endif
