#ifndef __OBOTCHA_BYTE_HPP__
#define __OBOTCHA_BYTE_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Number.hpp"
#include <cstddef>

namespace obotcha {

class _String;

#define byte uint8_t

DECLARE_SIMPLE_CLASS(Byte) IMPLEMENTS(Number)<byte>{
public:
    _Byte();
    
    _Byte(unsigned char v);

    _Byte(const Byte &v);
   
    byte toValue();

    bool equals(byte p);
    
    bool equals(const Byte &p);

    bool equals(const _Byte *p);

    void update(byte v);

    void update(const sp<_Byte> v);

    sp<_String> toHexString();

    sp<_String> toOctalString();

    sp<_String> toBinaryString();

    sp<_String> toString();

    static sp<_String> toString(byte i);
    
    static byte parseDecByte(const sp<_String>);

    static byte parseHexByte(const sp<_String>);

    static byte parseOctByte(const sp<_String>);

    static byte parseBinaryByte(const sp<_String>);

    static sp<_String> className();

    uint64_t hashcode();

    ~_Byte();

private:
    byte val;

};

}
#endif