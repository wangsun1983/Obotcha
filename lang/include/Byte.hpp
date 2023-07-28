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
    
    explicit _Byte(unsigned char v);
    
    explicit _Byte(const Byte &v);
    
    explicit _Byte(const sp<_String> &v);
    
    byte toValue() const;
    
    bool equals(Object p) override;

    bool sameAs(byte) const;
    
    void update(byte v);
    
    void update(const sp<_Byte> &v);
    
    sp<_String> toHexString() const;
    
    sp<_String> toOctalString() const;
    
    sp<_String> toBinaryString() const;
    
    sp<_String> toString() override;

    static sp<_String> ToString(byte i);
    
    static sp<_Byte> Parse(const sp<_String> &);

    static sp<_Byte> ParseDecString(const sp<_String> &);

    static sp<_Byte> ParseHexString(const sp<_String> &);

    static sp<_Byte> ParseOctString(const sp<_String> &);

    static sp<_Byte> ParseBinaryString(const sp<_String> &);

    static sp<_String> ClassName();

    uint64_t hashcode() const override;

    ~_Byte() override = default;

private:
    byte val;
};

} // namespace obotcha
#endif
