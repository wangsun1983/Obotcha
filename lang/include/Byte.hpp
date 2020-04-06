#ifndef __BYTE_HPP__
#define __BYTE_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Number.hpp"

namespace obotcha {

#define byte unsigned char

class _String;

DECLARE_SIMPLE_CLASS(Byte) IMPLEMENTS(Number)<byte>{
public:
    _Byte(unsigned char v);

    _Byte(Byte &v);
   
    byte toValue();

    bool equals(byte p);
    
    bool equals(Byte &p);

    bool equals(const _Byte *p);

    void update(byte v);

    void update(sp<_Byte> v);

    sp<_String> toHexString();

    sp<_String> toOctalString();

    sp<_String> toBinaryString();

    sp<_String> toString();

    static sp<_String> toString(byte i);
    
    static byte parseDecByte(sp<_String>);

    static byte parseHexByte(sp<_String>);

    static byte parseOctByte(sp<_String>);

    static byte parseBinaryByte(sp<_String>);

    ~_Byte();

private:
    byte val;

};

}
#endif