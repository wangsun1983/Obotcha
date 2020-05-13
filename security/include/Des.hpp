#ifndef __OBOTCHA_DES_HPP__
#define __OBOTCHA_DES_HPP__

#include "openssl/des.h"

#include "File.hpp"
#include "String.hpp"
#include "ByteArray.hpp"

namespace obotcha {

#define DES_KEY_SIZE 8

enum DesType {
    DesTypeECB,
    DesTypeCBC,
};

enum DesMode {
    DesEncrypt = DES_ENCRYPT,
    DesDecrypt = DES_DECRYPT
};

DECLARE_SIMPLE_CLASS(Des) {

public:
    _Des(int destype);

    _Des();

    void encrypt(File src,File des);
    void decrypt(File src,File des);
    
    ByteArray encrypt(ByteArray);
    ByteArray decrypt(ByteArray);

    String decrypt(String str);

    String encrypt(String str);

    int genKey(File);

    int genKey(String filepath);

    int genKey(const char * filepath);

    int genKey(File,String content);

    int genKey(String filepath,String content);

    int genKey(const char * filepath,String content);

    int loadKey(File);

    int loadKey(String);

    int loadKey(const char *);

private:

    int mDesType;

    void fileOperation(int mode,File input,File output);

    ByteArray _desECB(ByteArray data,DES_key_schedule *schedule,int mode);

    ByteArray _desCBC(ByteArray data,DES_key_schedule *schedule,DES_cblock *ivec,int mode);

    int _genKey(String content);

    int _genKey();

    int _saveKey(String filepath);
    
    DES_cblock mKey;

};

}
#endif
