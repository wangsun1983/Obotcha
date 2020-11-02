#ifndef __OBOTCHA_SECRET_KEY_GENERATOR_HPP__
#define __OBOTCHA_SECRET_KEY_GENERATOR_HPP__

#include "StrongPointer.hpp"
#include "Object.hpp"
#include "ByteArray.hpp"
#include "File.hpp"
#include "SecretKey.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(SecretKeyGenerator) {
public:

    static int genKey(String pubkey,String privkey,String params);

    static SecretKey loadKey(String path);
    static SecretKey loadKey(const char * path);
    static SecretKey loadKey(ByteArray content);
};

}

#endif
