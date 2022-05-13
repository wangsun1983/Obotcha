#ifndef __OBOTCHA_BYTE_HPP__
#define __OBOTCHA_BYTE_HPP__

#include "Number.hpp"
#include "Object.hpp"


namespace obotcha {

class _String;

#define byte uint8_t

DECLARE_CLASS(Byte) IMPLEMENTS(Number)<uint8_t> {
public:
    static const int __isReflected = 1;

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

    static sp<_Byte> parseDecByte(const sp<_String>);

    static sp<_Byte> parseHexByte(const sp<_String>);

    static sp<_Byte> parseOctByte(const sp<_String>);

    static sp<_Byte> parseBinaryByte(const sp<_String>);

    static sp<_String> className();

    uint64_t hashcode();

    ~_Byte();

private:
    byte val;
};

} // namespace obotcha
#endif
