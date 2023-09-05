#ifndef __OBOTCHA_KEY_VALUE_PAIR_HPP__
#define __OBOTCHA_KEY_VALUE_PAIR_HPP__

#include "Object.hpp"

namespace obotcha {

DECLARE_TEMPLATE_CLASS(Pair,T,U) {
public:
    _Pair(T key, U value):mKey(key),
                          mValue(value) {
    }

    T getKey() { 
        return mKey; 
    }

    U getValue() { 
        return mValue; 
    }

private:
    T mKey;
    U mValue;
};

} // namespace obotcha
#endif