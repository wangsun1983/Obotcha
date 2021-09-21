#ifndef __OBOTCHA_KEY_VALUE_PAIR_HPP__
#define __OBOTCHA_KEY_VALUE_PAIR_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_TEMPLATE_CLASS(KeyValuePair, 2) {
public:
    _KeyValuePair(T key, U value) {
        mkey = key;
        mvalue = value;
    }

    T getKey() { return mkey; }

    U getValue() { return mvalue; }

private:
    T mkey;
    U mvalue;
};

} // namespace obotcha
#endif