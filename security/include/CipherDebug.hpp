#ifndef __OBOTCHA_CIPHER_DEBUG_HPP__
#define __OBOTCHA_CIPHER_DEBUG_HPP__

extern "C" {
#include "openssl/err.h"
}

#include "Object.hpp"

namespace obotcha {

DECLARE_CLASS(CipherDebug) {
public:
    static void dumpSSLError();
};

}

#endif
