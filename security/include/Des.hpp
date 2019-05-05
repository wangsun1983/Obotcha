#ifndef __DES_HPP__
#define __DES_HPP__

#include <openssl/des.h>

#include "File.hpp"
#include "String.hpp"
#include "ByteArray.hpp"

namespace obotcha {

#define DES_KEY_SIZE 8

enum DesType {
    DesTypeEBC,
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

    ByteArray encrypt(ByteArray);

    void decrypt(File src,File des);

    ByteArray decrypt(ByteArray);

    void genKey(File);

    void genKey(String filepath);

    void genKey(const char * filepath);

    void genKey(File,String content);

    void genKey(String filepath,String content);

    void genKey(const char * filepath,String content);

    void loadKey(File);

    void loadKey(String);

    void loadKey(const char *);

private:

    int mDesType;

    void fileOperation(int mode,File input,File output);

    ByteArray _desECB(ByteArray data,DES_key_schedule *schedule,int mode);

    ByteArray _desCBC(ByteArray data,DES_key_schedule *schedule,DES_cblock *ivec,int mode);

    void _genKey(String content);

    void _genKey();

    void _saveKey(String filepath);
    
    DES_cblock mKey;

};

}
#endif
