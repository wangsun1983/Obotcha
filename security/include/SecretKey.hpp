#ifndef __OBOTCHA_SECRET_KEY_HPP__
#define __OBOTCHA_SECRET_KEY_HPP__

#include "StrongPointer.hpp"
#include "Object.hpp"
#include "ByteArray.hpp"
#include "File.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(SecretKey) {
public:
    _SecretKey();
    File getFile();
    ByteArray getContent();

private:
    File mSecretFile;
    ByteArray mSecretContent;
};

}

#endif
