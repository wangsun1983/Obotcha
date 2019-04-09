#ifndef __DES_HPP__
#define __DES_HPP__

extern "C" {
#include "des.h"
}

#include "File.hpp"
#include "String.hpp"
#include "ByteArray.hpp"

namespace obotcha {

#define DES_KEY_SIZE 8

DECLARE_SIMPLE_CLASS(Des) {

public:
    void encrypt(File src,File des);
    ByteArray encrypt(ByteArray);

    void decrypt(File src,File des);
    ByteArray decrypt(ByteArray);

    void genKey(File);

    void genKey(String);

    void genKey(const char *);

    void loadKey(File);

    void loadKey(String);

    void loadKey(const char *);

private:
    File key;

    static const int encryptMode = ENCRYPTION_MODE;
    static const int decryptMode = DECRYPTION_MODE;

    void fileOperation(int mode,File input,File output);

    ByteArray contentOperation(int mode,ByteArray content);

};

}
#endif
