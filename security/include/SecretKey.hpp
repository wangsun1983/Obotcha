#ifndef __OBOTCHA_SECRET_KEY_HPP__
#define __OBOTCHA_SECRET_KEY_HPP__

#include <any>

#include "Object.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(SecretKey) {
public:
    enum KeyType {
        KeyAES128 = 0,
        KeyAES192,
        KeyAES256,
        KeyAESCFB1,
        KeyAESCFB8,
        KeyAESCFB128,
        KeyAESOFB128,
        KeyDES,
        KeyRSA,
    };

    virtual std::any get() = 0;
    virtual int loadEncryptKey(String path) = 0;
    virtual int loadDecryptKey(String path) = 0;
    int generate(String decKeyFile,String encKeyFile,String params);
    int generate(String decKeyFile,String encKeyFile);

protected:
    virtual int generate(String decKeyFile,String encKeyFile,ArrayList<String>params) = 0;

};

}

#endif
