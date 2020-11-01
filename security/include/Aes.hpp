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
    _Aes();
    
    int genKey(String decKeyFile,String encKeyFile);
    int genKey(String decKeyFile,String encKeyFile,String content);
    
    ByteArray encrypt(ByteArray in);
    void encrypt(File in,File out);

    ByteArray decrypt(ByteArray in);
    void decrypt(File in,File out);

    void init(int mode,SecretKey key);

private:

    AES_KEY mEncryptKey;

    AES_KEY mDecryptKey;

    int _genKey(String content);

    int _genKey();

    int _saveKey(String filepath,int mode);

    ByteArray _aesECB(ByteArray data);

    ByteArray _aesCBC(ByteArray data,unsigned char *ivec);

    ByteArray _aseFile(File in,File out);

    int loadKey(File file,int mode);
};

}

#endif
