#ifndef __AES_HPP__
#define __AES_HPP__

#include "openssl/aes.h"

#include "File.hpp"
#include "String.hpp"
#include "ByteArray.hpp"

namespace obotcha {

enum DesType {
    AesTypeECB,
    AesTypeCBC,
};

enum DesMode {
    AesEncrypt = AES_ENCRYPT,
    AesDecrypt = AES_DECRYPT
};

enum AesFailReason {
    AesFailGenEncrypteKey = 200,
    AesFailGenDecrypteKey,
    AesFailKeyNotExits,
    AesFailKeyReadError,
};

DECLARE_SIMPLE_CLASS(Aes) {

public:
    _Aes();
    
    _Aes(int);

    int genKey(String decKeyFile,String encKeyFile);

    int genKey(String decKeyFile,String encKeyFile,String content);

    ByteArray encrypt(String str);
    
    void encrypt(File src,File des);
    ByteArray encrypt(ByteArray buff);

    void decrypt(File src,File des);
    ByteArray decrypt(ByteArray buff);

    int loadKey(File,int);

    int loadKey(String,int);

    int loadKey(const char *,int);

private:

    int mType;

    AES_KEY mEncryptKey;

    AES_KEY mDecryptKey;

    int _genKey(String content);

    int _genKey();

    int _saveKey(String filepath,int mode);

    ByteArray _aesECB(ByteArray data,int mode);

    ByteArray _aesCBC(ByteArray data,unsigned char *ivec,int mode);
};

}

#endif
