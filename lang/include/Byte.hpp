#ifndef __OBOTCHA_BYTE_HPP__
#define __OBOTCHA_BYTE_HPP__

#include "Number.hpp"
#include "Object.hpp"

namespace obotcha {

class _String;

using byte = std::uint8_t;

DECLARE_CLASS(Byte) IMPLEMENTS(Number)<uint8_t> {
public:
    static const int __isReflected = 1;

    _Byte();
    
    _Byte(unsigned char v);
    
    _Byte(const Byte &v);
    
    _Byte(sp<_String> &v);
    
    byte toValue();
    
    bool equals(byte p);
    
    bool equals(const Byte &p);
    
    bool equals(const _Byte *p);
    
    void update(byte v);
    
    void update(const sp<_Byte> &v);
    
    sp<_String> toHexString();
    
    sp<_String> toOctalString();
    
    sp<_String> toBinaryString();
    
    sp<_String> toString();

    static sp<_String> ToString(byte i);
    
    static sp<_Byte> Parse(const sp<_String> &);

    static sp<_Byte> ParseDecString(const sp<_String> &);

    static sp<_Byte> ParseHexString(const sp<_String> &);

    static sp<_Byte> ParseOctString(const sp<_String> &);

    static sp<_Byte> ParseBinaryString(const sp<_String> &);

    static sp<_String> ClassName();

    uint64_t hashcode();

    ~_Byte();

private:
    byte val;
};

} // namespace obotcha
#endif
