#ifndef __OBOTCHA_CIPHER_CREATOR_HPP__
#define __OBOTCHA_CIPHER_CREATOR_HPP__

#include "Object.hpp"
#include "Cipher.hpp"

namespace obotcha {

DECLARE_CLASS(CipherCreator) {
public:
    static Cipher getInstance(String);
    static Cipher getInstance(const char *);
};

}

#endif
