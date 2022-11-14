#ifndef __OBOTCHA_SECRET_KEY_CREATOR_HPP__
#define __OBOTCHA_SECRET_KEY_CREATOR_HPP__

#include "Object.hpp"
#include "SecretKey.hpp"

namespace obotcha {

DECLARE_CLASS(SecretKeyCreator) {
public:
    static SecretKey getInstance(String);
    static SecretKey getInstance(const char *);
};

}

#endif
