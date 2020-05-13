#ifndef __OBOTCHA_UUID_HPP__
#define __OBOTCHA_UUID_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"

#define UUID4_LEN 37

namespace obotcha {

DECLARE_SIMPLE_CLASS(UUID) {

public:
    _UUID();

    String toValue();

private:

    String uuid;

    uint64_t seed[2];

    uint64_t xorshift128plus(uint64_t *s);

    int init();

    void generate(char *);
};

}
#endif