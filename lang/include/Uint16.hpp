#ifndef __OBOTCHA_UINT16_HPP__
#define __OBOTCHA_UINT16_HPP__

#include <stdio.h>
#include <stdint.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Number.hpp"

namespace obotcha {

class _String;

DECLARE_SIMPLE_CLASS(Uint16) IMPLEMENTS(Number<uint16_t>){
public:
    _Uint16();
    
    _Uint16(uint16_t v);

    _Uint16(const Uint16 &v);

    uint16_t toValue();

    bool equals(const Uint16 &p);

    bool equals(uint16_t p);

    bool equals(const _Uint16 *p);

    void update(uint16_t v);

    void update(const sp<_Uint16> &v);

    sp<_String> toHexString();

    sp<_String> toOctalString();

    sp<_String> toBinaryString();

    sp<_String> toString();

    static sp<_String> toString(uint16_t i);
    
    static uint16_t parseDecUint16(const sp<_String> &);

    static uint16_t parseHexUint16(const sp<_String>&);

    static uint16_t parseOctUint16(const sp<_String>&);

    static uint16_t parseBinaryUint16(const sp<_String>&);

    static sp<_String> className();

    uint64_t hashcode();
    
    ~_Uint16();

    static const uint16_t MAX_VALUE = 0xFFFF;

    static const uint16_t MIN_VALUE = 0x0;

private:
    uint16_t val;
};

}
#endif
