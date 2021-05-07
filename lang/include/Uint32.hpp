#ifndef __OBOTCHA_UINT32_HPP__
#define __OBOTCHA_UINT32_HPP__

#include <stdio.h>
#include <stdint.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Number.hpp"

namespace obotcha {

class _String;

DECLARE_SIMPLE_CLASS(Uint32) IMPLEMENTS(Number<uint32_t>) {
public:
    _Uint32();
    
    _Uint32(uint32_t v);

    _Uint32(const Uint32 &v);

    uint32_t toValue();

    bool equals(const Uint32 &p);

    bool equals(uint32_t p);

    bool equals(const _Uint32 *p);

    void update(uint32_t v);

    void update(const sp<_Uint32> &v);

    sp<_String> toHexString();

    sp<_String> toOctalString();

    sp<_String> toBinaryString();

    sp<_String> toString();

    static sp<_String> toString(uint32_t i);
    
    static uint32_t parseDecUint32(const sp<_String>&);

    static uint32_t parseHexUint32(const sp<_String>&);

    static uint32_t parseOctUint32(const sp<_String>&);

    static uint32_t parseBinaryUint32(const sp<_String>&);

    static sp<_String> className();

    uint64_t hashcode();

    ~_Uint32();

    static const uint32_t MAX_VALUE = 0xFFFFFFFF;

    static const uint32_t MIN_VALUE = 0x0;

private:
    uint32_t val;
};

}
#endif
