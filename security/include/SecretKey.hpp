#ifndef __OBOTCHA_SECRET_KEY_HPP__
#define __OBOTCHA_SECRET_KEY_HPP__

#include "StrongPointer.hpp"
#include "Object.hpp"
#include "ByteArray.hpp"
#include "File.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(SecretKey) {
public:
    virtual void *get() = 0;
    virtual int loadEncryptKey(String path) = 0;
    virtual int loadDecryptKey(String path) = 0;
    int generate(String decKeyFile,String encKeyFile,String params);
protected:
    virtual int generate(String decKeyFile,String encKeyFile,ArrayList<String>params) = 0;

};

}

#endif
