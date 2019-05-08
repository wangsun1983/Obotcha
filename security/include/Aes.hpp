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

DECLARE_SIMPLE_CLASS(Aes) {

public:
    _Aes(int);

    void genKey(String filepath,int mode);

    void genKey(const char * filepath,int mode);

    void genKey(File,String content,int mode);

    void genKey(String filepath,String content,int mode);

    void genKey(const char * filepath,String content,int mode);

    String decode(String str);

    String encode(String str);
    
    ByteArray encode(ByteArray buff);

    ByteArray decode(ByteArray buff);

    void loadKey(File,int);

    void loadKey(String,int);

    void loadKey(const char *,int);

private:

    int mType;

    AES_KEY mEncryptKey;

    AES_KEY mDecryptKey;

    void _genKey(String content,int mode);

    void _genKey(int);

    void _saveKey(String filepath,int mode);

    ByteArray _aesECB(ByteArray data,int mode);

    ByteArray _aesCBC(ByteArray data,unsigned char *ivec,int mode);
};

}

#endif
