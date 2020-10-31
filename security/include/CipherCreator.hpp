#ifndef __OBOTCHA_CIPHER_CREATOR_HPP__
#define __OBOTCHA_CIPHER_CREATOR_HPP__

#include "StrongPointer.hpp"
#include "Object.hpp"
#include "Cipher.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(CipherCreator) {
public:
    static Cipher getInstance(String);
    static Cipher getInstance(const char *);

};

}

#endif
